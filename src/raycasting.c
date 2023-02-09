/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:22:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/09 16:38:54 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <time.h>

void	calc_side_delta_dist(t_pos_v **pos)
{
	(*pos)->ray.steping[0] = 1;
	if ((*pos)->ray.ray_dir[0] < 0)
		(*pos)->ray.steping[0] = -1;
	(*pos)->ray.steping[1] = 1;
	if ((*pos)->ray.ray_dir[1] < 0)
		(*pos)->ray.steping[1] = -1;
	if ((*pos)->ray.ray_dir[0] == 0)
		(*pos)->ray.delta_dist[0] = VERY_BIG_N;
	else
		(*pos)->ray.delta_dist[0] = fabs(1 / (*pos)->ray.ray_dir[0]);
	if ((*pos)->ray.ray_dir[1] == 0)
		(*pos)->ray.delta_dist[1] = VERY_BIG_N;
	else
		(*pos)->ray.delta_dist[1] = fabs(1 / (*pos)->ray.ray_dir[1]);
	(*pos)->ray.side_d_nd[0] = (*pos)->p_pos[0] - (*pos)->map_pos[0];
	if ((*pos)->ray.steping[0] > 0)
		(*pos)->ray.side_d_nd[0] = (*pos)->map_pos[0] + 1 - (*pos)->p_pos[0];
	(*pos)->ray.side_dist[0] = (*pos)->ray.side_d_nd[0]
		* (*pos)->ray.delta_dist[0];
	(*pos)->ray.side_d_nd[1] = (*pos)->p_pos[1] - (*pos)->map_pos[1];
	if ((*pos)->ray.steping[1] > 0)
		(*pos)->ray.side_d_nd[1] = (*pos)->map_pos[1] + 1 - (*pos)->p_pos[1];
	(*pos)->ray.side_dist[1] = (*pos)->ray.side_d_nd[1]
		* (*pos)->ray.delta_dist[1];
}

void	check_screenp_x_y_move(t_vars **vars)
{
	if ((*vars)->p_vec->ray.side_dist[0] < (*vars)->p_vec->ray.side_dist[1])
	{
		(*vars)->p_vec->ray.side_dist[0] += (*vars)->p_vec->ray.delta_dist[0];
		(*vars)->p_vec->map_pos[0] += (*vars)->p_vec->ray.steping[0];
		(*vars)->p_vec->ray.side = 0;
	}
	else
	{
		(*vars)->p_vec->ray.side_dist[1] += (*vars)->p_vec->ray.delta_dist[1];
		(*vars)->p_vec->map_pos[1] += (*vars)->p_vec->ray.steping[1];
		(*vars)->p_vec->ray.side = 1;
	}
}

int	did_ray_hit(t_vars **vars)
{
	return ((*vars)->map->map[((*vars)->p_vec->map_pos[1]
				* (*vars)->map->width)
			+ (*vars)->p_vec->map_pos[0]] == '1');
}

void	calc_rayds_to_face(t_vars **vars)
{
	if (!(*vars)->p_vec->ray.side)
	{
		(*vars)->p_vec->ray.wall_dist = (*vars)->p_vec->ray.side_dist[0]
			- (*vars)->p_vec->ray.delta_dist[0];
		(*vars)->p_vec->ray.face = WEST;
		if ((*vars)->p_vec->map_pos[0] < (*vars)->p_vec->p_pos[0])
			(*vars)->p_vec->ray.face = EAST;
		(*vars)->p_vec->ray.hit_pos = (*vars)->p_vec->p_pos[1]
			+ (*vars)->p_vec->ray.wall_dist * (*vars)->p_vec->ray.ray_dir[1];
	}
	else
	{
		(*vars)->p_vec->ray.wall_dist = (*vars)->p_vec->ray.side_dist[1]
			- (*vars)->p_vec->ray.delta_dist[1];
		(*vars)->p_vec->ray.face = SOUTH;
		if ((*vars)->p_vec->map_pos[1] > (*vars)->p_vec->p_pos[1])
			(*vars)->p_vec->ray.face = NORTH;
		(*vars)->p_vec->ray.hit_pos = (*vars)->p_vec->p_pos[0]
			+ (*vars)->p_vec->ray.wall_dist * (*vars)->p_vec->ray.ray_dir[0];
	}
	(*vars)->p_vec->line_height = (int)(W_H / (*vars)->p_vec->ray.wall_dist);
}

int	cast_rays(t_vars **vars)
{
	int	x_coord;

	set_screen_vect(&(*vars)->p_vec);
	x_coord = -1;
	while (++x_coord < W_W)
	{
		set_initial_x_rayd(vars, x_coord);
		calc_side_delta_dist(&(*vars)->p_vec);
		while (!(*vars)->p_vec->ray.hit_)
		{
			check_screenp_x_y_move(vars);
			(*vars)->p_vec->ray.hit_ = did_ray_hit(vars);
		}
		calc_rayds_to_face(vars);
		draw_line(*vars, x_coord, (*vars)->p_vec->ray.hit_pos);
	}
	draw_crosshair(&(*vars)->render_buffer);
	draw_minimap(&(*vars)->render_buffer, *vars);
	mlx_do_sync((*vars)->mlx);
	mlx_put_image_to_window((*vars)->mlx, (*vars)->win,
		(*vars)->render_buffer.img, 0, 0);
	return (1);
}
