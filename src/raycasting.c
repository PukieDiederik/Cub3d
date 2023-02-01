/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:22:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/01/31 23:59:54 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// index of coordinate = desired y * width + desired x - in indexed starting from 0
#include "cub3d.h"
#include <stdio.h>

void	set_starting_rdata(t_pos_v	*pos)
{
	pos->ray.ray_dir[0] = 0;
	pos->ray.ray_dir[1] = 0;
	pos->ray.delta_dist[0] = 0;
	pos->ray.delta_dist[1] = 0;
	pos->ray.side_dist[0] = 0;
	pos->ray.side_dist[1] = 0;
}

void	set_starting_pdata(t_pos_v *pos, t_vars *vars)
{
	vars = *get_vars(); 
	pos->p_pos[0] = vars->map->player_spawn_x;
	pos->p_pos[1] = vars->map->player_spawn_y;
	pos->map_pos[0] = (int)pos->p_pos[0];
	pos->map_pos[1] = (int)pos->p_pos[1];
	if (vars->map->player_facing == 'N' ||	vars->map->player_facing == 'S')
	{
		pos->p_dir[1] = 1;
		if (vars->map->player_facing == 'N')
			pos->p_dir[1] = -1;
		pos->p_dir[0] = 0;
	}
	if (vars->map->player_facing == 'E' ||	vars->map->player_facing == 'W')
	{
		pos->p_dir[0] = 1;
		if (vars->map->player_facing == 'W')
			pos->p_dir[1] = -1;
		pos->p_dir[1] = 0;
	}
	pos->camera_x = 0;
	set_starting_rdata(pos);
	set_screen_vect(pos);
}

void	calc_side_delta_dist(t_pos_v *pos)
{
	//set ray stepping
	pos->ray.steping[0] = 1;
	if (pos->ray.ray_dir[0] < 0)
		pos->ray.steping[0] = -1;
	pos->ray.steping[1] = 1;
	if (pos->ray.ray_dir[1] < 0)
		pos->ray.steping[1] = -1;
	printf("ray stepping = %dx %dy\n", pos->ray.steping[0], pos->ray.steping[1]);
	//set ray distance from edge of current position square to next x and y edge
	pos->ray.delta_dist[0] = fabs(1 / pos->ray.ray_dir[0]);
	pos->ray.delta_dist[1] = fabs(1 / pos->ray.ray_dir[1]);
	printf("ray desta distances = %lfx %lfy\n", pos->ray.delta_dist[0], pos->ray.delta_dist[1]);

	//calculate distance from current position to edge of square in x direction
	pos->ray.side_d_nd[0] = pos->p_pos[0] - pos->map_pos[0];
	if (pos->ray.steping[0] > 0)
		pos->ray.side_d_nd[0] = pos->map_pos[0] + 1 - pos->p_pos[0];
	pos->ray.side_dist[0] = pos->ray.side_d_nd[0] * pos->ray.delta_dist[0];
	//calculate distance from current position to edge of square in y direction
	pos->ray.side_d_nd[1] = pos->p_pos[1] - pos->map_pos[1];
	if (pos->ray.steping[1] > 1)
		pos->ray.side_d_nd[1] = pos->map_pos[1] + 1 - pos->p_pos[1];
	pos->ray.side_dist[1] = pos->ray.side_d_nd[1] * pos->ray.delta_dist[1];
}

int	cast_rays(t_vars *vars)
{
	t_pos_v	ppvs;
	int		x_coord;
	static int	i;


	ppvs = vars->p_vec;
	if (!i){
		printf("initialized player data:\nposition vector = (%lf, %lf)\ndirection vector = (%lf, %lf)\nScreen = (%lf, %lf)\n",ppvs.p_pos[0], ppvs.p_pos[1], ppvs.p_dir[0], ppvs.p_dir[1], ppvs.screen[0], ppvs.screen[1]);
		i++;
	}
	set_starting_pdata(&ppvs, vars);
	x_coord = -1;
	while (++x_coord < WIN_WIDTH)
	{
		ppvs.ray.hit_ = 0;
		ppvs.camera_x = 2.0 * x_coord / (double)WIN_WIDTH - 1;
		ppvs.ray.ray_dir[0] = ppvs.p_dir[0] + ppvs.screen[0] * ppvs.camera_x;
		ppvs.ray.ray_dir[1] = ppvs.p_dir[1] + ppvs.screen[1] * ppvs.camera_x;
		printf("ray direction = %lfx %lfy\n", ppvs.ray.ray_dir[0], ppvs.ray.ray_dir[1]);
		calc_side_delta_dist(&ppvs);
		while (!ppvs.ray.hit_)
		{
			if (ppvs.ray.side_dist[0] < ppvs.ray.side_dist[1])
			{
				ppvs.ray.side_dist[0] += ppvs.ray.delta_dist[0];
				ppvs.map_pos[0] += ppvs.ray.steping[0];
				ppvs.ray.side = 0;
			}
			else
			{
				ppvs.ray.side_dist[1] += ppvs.ray.delta_dist[1];
				ppvs.map_pos[1] += ppvs.ray.steping[1];
				ppvs.ray.side = 1;
			}
			printf("desired y = %d, width = %d, desired x = %d, map position =%d\n",
			ppvs.map_pos[1], vars->map->width, ppvs.map_pos[0], ((ppvs.map_pos[1] * vars->map->width)) + ppvs.map_pos[0]);
			if (vars->map->map[(ppvs.map_pos[1] * vars->map->width) + ppvs.map_pos[0]] == '1')
				ppvs.ray.hit_ = 1;
		}
		if (ppvs.ray.side)
			ppvs.ray.wall_dist = ppvs.ray.side_dist[0] - ppvs.ray.delta_dist[0];
		else
			ppvs.ray.wall_dist = ppvs.ray.side_dist[1] - ppvs.ray.delta_dist[1];



	}
	return (1);
}