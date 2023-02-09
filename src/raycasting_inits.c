/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_inits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:17:31 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/08 16:18:56 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_starting_rdata(t_vars **vars)
{
	(*vars)->p_vec->ray.ray_dir[0] = 0;
	(*vars)->p_vec->ray.ray_dir[1] = 0;
	(*vars)->p_vec->ray.delta_dist[0] = 0;
	(*vars)->p_vec->ray.delta_dist[1] = 0;
	(*vars)->p_vec->ray.side_dist[0] = 0;
	(*vars)->p_vec->ray.side_dist[1] = 0;
}

int	set_starting_pdata(t_vars **vars)
{	
	(*vars)->p_vec = malloc(sizeof(t_pos_v));
	if (!(*vars)->p_vec || FOV_DEG > 179 || FOV_DEG < 1)
	{
		free((*vars)->p_vec);
		return (0);
	}
	(*vars)->p_vec->p_pos[0] = (*vars)->map->player_spawn_x + 0.5;
	(*vars)->p_vec->p_pos[1] = (*vars)->map->player_spawn_y + 0.5;
	(*vars)->p_vec->p_dir[1] = 0;
	(*vars)->p_vec->p_dir[0] = 0;
	if ((*vars)->map->player_facing == 'N')
		(*vars)->p_vec->p_dir[1] = -1;
	else if ((*vars)->map->player_facing == 'S')
		(*vars)->p_vec->p_dir[1] = 1;
	else if (((*vars)->map->player_facing == 'W'))
		(*vars)->p_vec->p_dir[0] = -1;
	else if (((*vars)->map->player_facing == 'E'))
		(*vars)->p_vec->p_dir[0] = 1;
	(*vars)->p_vec->camera_x = 0;
	set_starting_rdata(vars);
	return (1);
}

void	set_initial_x_rayd(t_vars **vars, int x_coord)
{
	(*vars)->p_vec->ray.hit_ = 0;
	(*vars)->p_vec->map_pos[0] = (int)(*vars)->p_vec->p_pos[0];
	(*vars)->p_vec->map_pos[1] = (int)(*vars)->p_vec->p_pos[1];
	(*vars)->p_vec->camera_x = (2.0 * x_coord / (double)W_W) - 1;
	(*vars)->p_vec->ray.ray_dir[0] = (*vars)->p_vec->p_dir[0]
		+ -(*vars)->p_vec->screen[0] * (*vars)->p_vec->camera_x;
	(*vars)->p_vec->ray.ray_dir[1] = (*vars)->p_vec->p_dir[1]
		+ -(*vars)->p_vec->screen[1] * (*vars)->p_vec->camera_x;
}
