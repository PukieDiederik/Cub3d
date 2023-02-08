/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:59:01 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/08 16:13:18 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx_img *r_buf, int x, int y, int color)
{
	char	*dst;

	dst = r_buf->addr + (y * r_buf->line_length
			+ x * (r_buf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	*get_img_color(t_mlx_img *img, int x, int y)
{
	char	*dst_b;

	if (!img)
		return (0);
	dst_b = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	return ((unsigned int *)(dst_b));
}

void	set_values(	int *ceiling_index, int *floor_index,
	double *hit_x, int *img_init_i)
{
	t_vars	*vars;

	vars = *get_vars();
	*ceiling_index = (W_H - vars->p_vec->line_height) / 2;
	*img_init_i = 0;
	if (vars->p_vec->line_height > W_H)
	{
		*img_init_i = (vars->p_vec->line_height - W_H) / 2;
		*ceiling_index = 0;
	}
	*floor_index = W_H - *ceiling_index;
	*hit_x -= (int)*hit_x;
}

void	draw_line(t_vars *vars, int x, double hit_x)
{
	int		i;
	int		ceiling_index;
	int		floor_index;
	double	img_y;
	int		img_init_i;

	set_values(&ceiling_index, &floor_index, &hit_x, &img_init_i);
	i = -1;
	while (++i < ceiling_index)
		my_mlx_pixel_put(&vars->render_buffer, x, i,
			vars->tex_info.ceiling_color);
	i--;
	while (++i < floor_index)
	{
		img_y = ((double)(i - ceiling_index + img_init_i)
				/ vars->p_vec->line_height);
		my_mlx_pixel_put(&vars->render_buffer, x, i,
			*get_img_color(&vars->tex_info.textures[vars->p_vec->ray.face],
				hit_x * vars->tex_info.textures[vars->p_vec->ray.face].width,
				img_y * vars->tex_info.textures[vars->p_vec->ray.face].height));
	}
	i--;
	while (++i < W_H && vars->p_vec->line_height < W_H)
		my_mlx_pixel_put(&vars->render_buffer, x, i,
			vars->tex_info.floor_color);
}
