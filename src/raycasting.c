/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:22:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/03 17:34:25 by leferrei         ###   ########.fr       */
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
	if ((*vars)->map->player_facing == 'N' ||	(*vars)->map->player_facing == 'S')
	{
		(*vars)->p_vec->p_dir[1] = 1;
		if ((*vars)->map->player_facing == 'N')
			(*vars)->p_vec->p_dir[1] = -1;
		(*vars)->p_vec->p_dir[0] = 0;
	}
	if ((*vars)->map->player_facing == 'E' ||	(*vars)->map->player_facing == 'W')
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
	//set ray stepping
	(*pos)->ray.steping[0] = 1;
	if ((*pos)->ray.ray_dir[0] < 0)
		(*pos)->ray.steping[0] = -1;
	(*pos)->ray.steping[1] = 1;
	if ((*pos)->ray.ray_dir[1] < 0)
		(*pos)->ray.steping[1] = -1;
	//printf("ray stepping = %dx %dy\n", (*pos)->ray.steping[0], (*pos)->ray.steping[1]);
	//set ray distance from edge of current position square to next x and y edge
	//printf("(*pos)->ray.ray_dir[0] = %lf (*pos)->ray.ray_dir[1] = %lf\n", (*pos)->ray.ray_dir[0], (*pos)->ray.ray_dir[1]);
	
	if ((*pos)->ray.ray_dir[0] == 0 && printf("x zero condition\n"))
		(*pos)->ray.delta_dist[0] = 1000000000000000019884624838656.00;
	else
		(*pos)->ray.delta_dist[0] = fabs(1 / (*pos)->ray.ray_dir[0]);



	if ((*pos)->ray.ray_dir[1] == 0 && printf("y zero condition\n"))
		(*pos)->ray.delta_dist[1] = 1000000000000000019884624838656.00;
	else
		(*pos)->ray.delta_dist[1] = fabs(1 / (*pos)->ray.ray_dir[1]);

	//printf("ray desta distances = %lfx %lfy\n", (*pos)->ray.delta_dist[0], (*pos)->ray.delta_dist[1]);
	//calculate distance from current position to edge of square in x direction
	(*pos)->ray.side_d_nd[0] = (*pos)->p_pos[0] - (*pos)->map_pos[0];
	if ((*pos)->ray.steping[0] > 0)
		(*pos)->ray.side_d_nd[0] = (*pos)->map_pos[0] + 1 - (*pos)->p_pos[0];

	(*pos)->ray.side_dist[0] = (*pos)->ray.side_d_nd[0] * (*pos)->ray.delta_dist[0];


	//calculate distance from current position to edge of square in y direction
	(*pos)->ray.side_d_nd[1] = (*pos)->p_pos[1] - (*pos)->map_pos[1];
	if ((*pos)->ray.steping[1] > 0)
		(*pos)->ray.side_d_nd[1] = (*pos)->map_pos[1] + 1 - (*pos)->p_pos[1];

	(*pos)->ray.side_dist[1] = (*pos)->ray.side_d_nd[1] * (*pos)->ray.delta_dist[1];
}
void    my_mlx_pixel_put(t_mlx_img *r_buf, int x, int y, int color)
{
        char    *dst;

        dst = r_buf->addr + (y * r_buf->line_length + x * (r_buf->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
}

int	get_img_color(t_mlx_img *img, int x, int y)
{
	char	*dst_b;

	dst_b = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*dst_b);
}
void	draw_line(t_vars *vars, int x)
{
	int	i;
	int	ceiling_index;
	int	floor_index;
	int	wall_color;


	if (vars->p_vec->line_height > WIN_HEIGHT)
		vars->p_vec->line_height = WIN_HEIGHT;
	if (vars->p_vec->ray.face == 1)
		wall_color = 0xFF8A00;
	if (vars->p_vec->ray.face == 2)
		wall_color = 0xA000CB;
	if (vars->p_vec->ray.face == 3)
		wall_color = 0x00B7B2;
	if (vars->p_vec->ray.face == 4)
		wall_color = 0xCCCCCC;
	ceiling_index = (WIN_HEIGHT - vars->p_vec->line_height) / 2;
	floor_index = WIN_HEIGHT - ceiling_index;
	//printf("floor index  = %d, ceiling index = %d\n", floor_index, ceiling_index);
	i = -1;
	while (++i < ceiling_index)
		my_mlx_pixel_put(&vars->render_buffer, x, i, vars->tex_info.ceiling_color);
	i--;
	while(++i < floor_index)
		my_mlx_pixel_put(&vars->render_buffer, x, i, wall_color);
	i--;
	while(++i < WIN_HEIGHT)
		my_mlx_pixel_put(&vars->render_buffer, x, i, vars->tex_info.floor_color);
		
}


int	exec_loop_contition(int	*x_coord, t_vec *last_pos, t_vec *last_dir, t_vars *vars)
{

	return (++(*x_coord) < WIN_WIDTH && (compate_vectors(last_pos, &vars->p_vec->p_pos)
			|| compate_vectors(last_dir, &vars->p_vec->p_dir)));
}
int	cast_rays(t_vars **vars)
{
	int				x_coord;
	static t_vec	last_pos;
	static t_vec	last_dir;
	int	exec = 0;
	double time_spent = 0.0;
    clock_t begin = clock();
	//if (!init && ++init)
	//	set_starting_pdata(vars);
	set_screen_vect(&(*vars)->p_vec);
	x_coord = -1;
	printf("played dir vector on initial cast_rays = %lfx %lfy\n", (*vars)->p_vec->p_dir[0], (*vars)->p_vec->p_dir[1]);
	printf("current payer position = %lfx %lfy\n", (*vars)->p_vec->p_pos[0], (*vars)->p_vec->p_pos[1]);
	printf("current screen vector data + %lfx %lfy\n",(*vars)->p_vec->screen[0], (*vars)->p_vec->screen[1]);
	while (++x_coord < WIN_WIDTH)
	{
		(*vars)->p_vec->ray.hit_ = 0;
		(*vars)->p_vec->map_pos[0] = (int)(*vars)->p_vec->p_pos[0];
		(*vars)->p_vec->map_pos[1] = (int)(*vars)->p_vec->p_pos[1];
		(*vars)->p_vec->camera_x = (2.0 * x_coord / (double)WIN_WIDTH) - 1;
		(*vars)->p_vec->ray.ray_dir[0] = (*vars)->p_vec->p_dir[0] +
			-(*vars)->p_vec->screen[0] * (*vars)->p_vec->camera_x;
		(*vars)->p_vec->ray.ray_dir[1] = (*vars)->p_vec->p_dir[1] +
			-(*vars)->p_vec->screen[1] * (*vars)->p_vec->camera_x;
		//normalize_vector(&(*vars)->p_vec->ray.ray_dir);
		//printf("ray direction = %lfx %lfy\n", (*vars)->p_vec->ray.ray_dir[0], (*vars)->p_vec->ray.ray_dir[1]);
		calc_side_delta_dist(&(*vars)->p_vec);
		while (!(*vars)->p_vec->ray.hit_)
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
			//printf("desired y = %d, width = %d, desired x = %d, map position =%d\n",
			//(*vars)->p_vec->map_pos[1], (*vars)->map->width, (*vars)->p_vec->map_pos[0], (((*vars)->p_vec->map_pos[1] * (*vars)->map->width)) + (*vars)->p_vec->map_pos[0]);
			if ((*vars)->map->map[((*vars)->p_vec->map_pos[1] * (*vars)->map->width) +
				(*vars)->p_vec->map_pos[0]] == '1')
				(*vars)->p_vec->ray.hit_ = 1;

		}
	//	printf("side = %d\n", (*vars)->p_vec->ray.side);
		if (!(*vars)->p_vec->ray.side)
		{
			(*vars)->p_vec->ray.wall_dist = (*vars)->p_vec->ray.side_dist[0] -
				(*vars)->p_vec->ray.delta_dist[0];
			(*vars)->p_vec->ray.face = 2;
			if ((*vars)->p_vec->map_pos[0] < (*vars)->p_vec->p_pos[0])
				(*vars)->p_vec->ray.face = 4;
		}
		else
		{
			(*vars)->p_vec->ray.wall_dist = (*vars)->p_vec->ray.side_dist[1] -
				(*vars)->p_vec->ray.delta_dist[1];

		(*vars)->p_vec->ray.face = 1;
			if ((*vars)->p_vec->map_pos[1] > (*vars)->p_vec->p_pos[1])
				(*vars)->p_vec->ray.face = 3;

		}
		(*vars)->p_vec->line_height = (int)(WIN_HEIGHT / (*vars)->p_vec->ray.wall_dist);
		//printf("line_height at %d = %d / %lf = %d\n", x_coord,WIN_HEIGHT,  (*vars)->p_vec->ray.wall_dist, (*vars)->p_vec->line_height);
		//(*vars)->p_vec->line_height = 380;
		draw_line(*vars, x_coord);
		exec = 1;
	}
	if (exec)
	{
		clock_t end = clock();
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   		printf("The time per frame was = %f - fps = %d\n", time_spent, (int)(1/time_spent));
	}
	// printf("exited at x = %d\n", x_coord);
	set_vect_to_vect(&last_dir, &(*vars)->p_vec->p_dir);
	set_vect_to_vect(&last_pos, &(*vars)->p_vec->p_pos);
	mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->render_buffer.img, 0, 0);
	return (1);
}