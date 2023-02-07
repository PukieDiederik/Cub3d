/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:55:16 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/07 17:54:59 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_border(t_mlx_img *img)
{
	int	i;
	int	k;

	i = -1;
	while (++i < mm_s() + mm_b_s() + mm_spacer())
	{
		k = -1;
		while (++k < mm_s() + mm_b_s() + mm_spacer())
			if ((i < mm_b_s() || i > mm_s()) || (k < mm_b_s() || k > mm_s()))
				my_mlx_pixel_put(img, i + mm_spacer(), k + mm_spacer(), 0x222222);
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
		c[0] = r * cos(i * d_to_r());
		c[1] = r * sin(i * d_to_r());
		if (get_angle_between_vec(&vars->p_vec->p_dir, &c) < 45
			&& get_angle_between_vec(&vars->p_vec->p_dir, &c) > -45)
			r = 7;
		while (--r > -1)
		{
			c[0] = r * cos(i * d_to_r());
			c[1] = r * sin(i * d_to_r());
			my_mlx_pixel_put(img,
				(int)((*abs_p)[0] + mm_spacer() + mm_b_s() + c[0]),
				(int)((*abs_p)[1] + mm_spacer() + mm_b_s() + c[1]), CH_COLOR);
		}
		r = 4;
	}
}

static void	draw_player_position(t_mlx_img *img, t_vars *vars)
{
	t_vec	abs_p;

	abs_p[0] = vars->p_vec->p_pos[0] / vars->map->width;
	abs_p[0] = ((double)abs_p[0] - (int)abs_p[0]) * mm_s();
	abs_p[1] = vars->p_vec->p_pos[1] / vars->map->height;
	abs_p[1] = ((double)abs_p[1] - (int)abs_p[1]) * mm_s();
	draw_player_circle(img, &abs_p, vars);
}

static void	paint_mm_pos(t_mlx_img *img, t_vec map, t_vars *vars, int c[2])
{
	if (vars->map->map[(int)(map[1] * vars->map->width + map[0])] == '1')
		my_mlx_pixel_put(img,
			c[0] + mm_b_s() + mm_spacer(), c[1] + mm_b_s() + mm_spacer(),
			MM_WALL_C);
	else if ((vars->map->map[(int)(map[1] * vars->map->width + map[0])] == '0'))
		my_mlx_pixel_put(img,
			c[0] + mm_b_s() + mm_spacer(), c[1] + mm_b_s() + mm_spacer(),
			vars->tex_info.floor_color);
	else
		my_mlx_pixel_put(img,
			c[0] + mm_b_s() + mm_spacer(), c[1] + mm_b_s() + mm_spacer(),
			0x222222);
}

void	draw_minimap(t_mlx_img *img, t_vars	*vars)
{
	int		c[2];
	t_vec	map;

	draw_minimap_border(img);
	c[0] = -1;
	while (++c[0] < mm_s())
	{
		map[0] = (double)c[0] / mm_s();
		map[0] -= (int)map[0];
		map[0] = (int)(map[0] * vars->map->width);
		c[1] = -1;
		while (++c[1] < mm_s())
		{
			map[1] = (double)c[1] / mm_s();
			map[1] -= (int)map[1];
			map[1] = (int)(map[1] * vars->map->height);
			paint_mm_pos(img, map, vars, c);
		}
	}
	draw_player_position(img, vars);
}
