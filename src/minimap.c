/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:55:16 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/07 17:15:20 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_border(t_mlx_img *img)
{
	int	i;
	int	k;

	i = -1;
	while (++i < MM_W + MM_B_W + MM_SPACER)
	{
		k = -1;
		while (++k < MM_H + MM_B_H + MM_SPACER)
			if ((i < MM_B_W || i > MM_W) || (k < MM_B_H || k > MM_H))
				my_mlx_pixel_put(img, i + MM_SPACER, k + MM_SPACER, 0x222222);
	}
}

static void	draw_player_circle(t_mlx_img *img, t_vec *abs_p, t_vars *vars)
{
	int		i;
	int		r;
	t_vec	c;

	i = -1;
	r = 4;
	while (++i < 360.0)
	{
		c[0] = r * cos(i * DEG_TO_RAD);
		c[1] = r * sin(i * DEG_TO_RAD);
		if (get_angle_between_vec(&vars->p_vec->p_dir, &c) < 45
			&& get_angle_between_vec(&vars->p_vec->p_dir, &c) > -45)
			r = 7;
		while (--r > -1)
		{
			c[0] = r * cos(i * DEG_TO_RAD);
			c[1] = r * sin(i * DEG_TO_RAD);
			my_mlx_pixel_put(img,
				(int)((*abs_p)[0] + MM_SPACER + MM_B_W + c[0]),
				(int)((*abs_p)[1] + MM_SPACER + MM_B_H + c[1]), CH_COLOR);
		}
		r = 4;
	}
}

static void	draw_player_position(t_mlx_img *img, t_vars *vars)
{
	t_vec	abs_p;

	abs_p[0] = vars->p_vec->p_pos[0] / vars->map->width;
	abs_p[0] = ((double)abs_p[0] - (int)abs_p[0]) * MM_W;
	abs_p[1] = vars->p_vec->p_pos[1] / vars->map->height;
	abs_p[1] = ((double)abs_p[1] - (int)abs_p[1]) * MM_H;
	draw_player_circle(img, &abs_p, vars);
}

static void	paint_mm_pos(t_mlx_img *img, t_vec map, t_vars *vars, int c[2])
{
	if (vars->map->map[(int)(map[1] * vars->map->width + map[0])] == '1')
		my_mlx_pixel_put(img,
			c[0] + MM_B_W + MM_SPACER, c[1] + MM_B_H + MM_SPACER,
			MM_WALL_C);
	else if ((vars->map->map[(int)(map[1] * vars->map->width + map[0])] == '0'))
		my_mlx_pixel_put(img,
			c[0] + MM_B_W + MM_SPACER, c[1] + MM_B_H + MM_SPACER,
			vars->tex_info.floor_color);
	else
		my_mlx_pixel_put(img,
			c[0] + MM_B_W + MM_SPACER, c[1] + MM_B_H + MM_SPACER,
			0x222222);
}

void	draw_minimap(t_mlx_img *img, t_vars	*vars)
{
	int		c[2];
	t_vec	map;

	draw_minimap_border(img);
	c[0] = -1;
	while (++c[0] < MM_W)
	{
		map[0] = (double)c[0] / MM_W;
		map[0] -= (int)map[0];
		map[0] = (int)(map[0] * vars->map->width);
		c[1] = -1;
		while (++c[1] < MM_H)
		{
			map[1] = (double)c[1] / MM_H;
			map[1] -= (int)map[1];
			map[1] = (int)(map[1] * vars->map->height);
			paint_mm_pos(img, map, vars, c);
		}
	}
	draw_player_position(img, vars);
}
