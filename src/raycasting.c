/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:22:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/06 22:03:57 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// index of coordinate = desired y * width + desired x - in indexed starting from 0
#include "cub3d.h"
#include <stdio.h>
#include <time.h>

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
		return (0);
	(*vars)->p_vec->p_pos[0] = (*vars)->map->player_spawn_x + 0.5;
	(*vars)->p_vec->p_pos[1] = (*vars)->map->player_spawn_y + 0.5;
	if ((*vars)->map->player_facing == 'N'
		|| (*vars)->map->player_facing == 'S')
	{
		(*vars)->p_vec->p_dir[1] = 1;
		if ((*vars)->map->player_facing == 'N')
			(*vars)->p_vec->p_dir[1] = -1;
		(*vars)->p_vec->p_dir[0] = 0;
	}
	if ((*vars)->map->player_facing == 'E'
		|| (*vars)->map->player_facing == 'W')
	{
		(*vars)->p_vec->p_dir[0] = 1;
		if ((*vars)->map->player_facing == 'W')
			(*vars)->p_vec->p_dir[1] = -1;
		(*vars)->p_vec->p_dir[1] = 0;
	}
	(*vars)->p_vec->camera_x = 0;
	set_starting_rdata(vars);
	return (1);
}

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

void	my_mlx_pixel_put(t_mlx_img *r_buf, int x, int y, int color)
{
	char	*dst;

	dst = r_buf->addr + (y * r_buf->line_length
			+ x * (r_buf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	*get_img_color(t_mlx_img *img, int x, int y)
{
	char *dst_b;

	if (!img)
		return (0);
	dst_b = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	return ((unsigned int *)(dst_b));
}

void	draw_line(t_vars *vars, int x, double hit_x)
{
	int	i;
	int	ceiling_index;
	int	floor_index;
	double	img_y;
	int	img_init_i;

	ceiling_index = (W_H - vars->p_vec->line_height) / 2;
	img_init_i = 0;
	if (vars->p_vec->line_height > W_H)
	{
		img_init_i = (vars->p_vec->line_height - W_H) / 2;
		ceiling_index = 0;
	}
	floor_index = W_H - ceiling_index;
	hit_x -= (int)hit_x;
	i = -1;
	while (++i < ceiling_index)
		my_mlx_pixel_put(&vars->render_buffer, x, i,
			vars->tex_info.ceiling_color);
	i --;
	while(++i < floor_index)
	{
		img_y = ((double)(i - ceiling_index + img_init_i) / vars->p_vec->line_height);
		my_mlx_pixel_put(&vars->render_buffer, x, i,
			*get_img_color(&vars->tex_info.textures[vars->p_vec->ray.face],
			hit_x * vars->tex_info.textures[vars->p_vec->ray.face].width,
			img_y * vars->tex_info.textures[vars->p_vec->ray.face].height));
	}
	i -= 2;
	while(++i < W_H && vars->p_vec->line_height < W_H)
		my_mlx_pixel_put(&vars->render_buffer, x, i,
			vars->tex_info.floor_color);
}


int	exec_loop_contition(int	*x_coord, t_vec *last_pos, t_vec *last_dir, t_vars *vars)
{

	return (++(*x_coord) < W_W && (compate_vectors(last_pos,
		&vars->p_vec->p_pos)
			|| compate_vectors(last_dir, &vars->p_vec->p_dir)));
}

void	set_initial_x_rayd(t_vars **vars, int x_coord)
{
	(*vars)->p_vec->ray.hit_ = 0;
	(*vars)->p_vec->map_pos[0] = (int)(*vars)->p_vec->p_pos[0];
	(*vars)->p_vec->map_pos[1] = (int)(*vars)->p_vec->p_pos[1];
	(*vars)->p_vec->camera_x = (2.0 * x_coord / (double)W_W) - 1;
	(*vars)->p_vec->ray.ray_dir[0] = (*vars)->p_vec->p_dir[0] +
		-(*vars)->p_vec->screen[0] * (*vars)->p_vec->camera_x;
	(*vars)->p_vec->ray.ray_dir[1] = (*vars)->p_vec->p_dir[1] +
		-(*vars)->p_vec->screen[1] * (*vars)->p_vec->camera_x;
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
		* (*vars)->map->width) + (*vars)->p_vec->map_pos[0]] == '1');
}

//side wall distances are calculated with xvalue because ray is cast from perpendicluar to me, the screen
//it is not a side when x increases not because of that,
//but because if y hit first and only after x also hit it was a side before x hit
//side hit position is calculated with ray dir Y and pos Y because to my view it is a side, meaning the y is the image x	
void	calc_rayds_to_face(t_vars **vars)
{
	if (!(*vars)->p_vec->ray.side)
	{
		(*vars)->p_vec->ray.wall_dist = (*vars)->p_vec->ray.side_dist[0] -
			(*vars)->p_vec->ray.delta_dist[0];
		(*vars)->p_vec->ray.face = 1;
		if ((*vars)->p_vec->map_pos[0] < (*vars)->p_vec->p_pos[0])
			(*vars)->p_vec->ray.face = 3;
		(*vars)->p_vec->ray.hit_pos = (*vars)->p_vec->p_pos[1] + (*vars)->p_vec->ray.wall_dist * (*vars)->p_vec->ray.ray_dir[1];
	}
	else
	{
		(*vars)->p_vec->ray.wall_dist = (*vars)->p_vec->ray.side_dist[1] -
			(*vars)->p_vec->ray.delta_dist[1];
		(*vars)->p_vec->ray.face = 0;
		if ((*vars)->p_vec->map_pos[1] > (*vars)->p_vec->p_pos[1])
			(*vars)->p_vec->ray.face = 2;
		(*vars)->p_vec->ray.hit_pos = (*vars)->p_vec->p_pos[0] + (*vars)->p_vec->ray.wall_dist * (*vars)->p_vec->ray.ray_dir[0];

	}
	(*vars)->p_vec->line_height = (int)(W_H / (*vars)->p_vec->ray.wall_dist);
}

int	cast_rays(t_vars **vars)
{
	int	x_coord;
	int	exec = 0;
	static int	times_rendered;
	static int		total_f;
	double time_spent = 0.0;
    clock_t begin = clock();
	
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
		exec = 1;
	}
	draw_crosshair(&(*vars)->render_buffer);
	if (exec)
	{
		clock_t end = clock();
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		total_f += (int)(1/time_spent);
		times_rendered++;
   		printf("The time per frame was = %f - avg fps = %d\n", time_spent, total_f / times_rendered);
	}
	mlx_do_sync((*vars)->mlx);
	mlx_put_image_to_window((*vars)->mlx, (*vars)->win,
		(*vars)->render_buffer.img, 0, 0);
	return (1);
}