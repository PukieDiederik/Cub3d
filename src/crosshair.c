/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:37:52 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/07 17:16:36 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ch_outline(t_mlx_img *img, int i, int color)
{
	my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i, W_H / 2 - 2, color);
	my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i, W_H / 2 - 2, color);
	my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i, W_H / 2 - 1, color);
	my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i, W_H / 2 - 1, color);
	my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i, W_H / 2 + 1, color);
	my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i, W_H / 2 + 1, color);
	my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i, W_H / 2 + 2, color);
	my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i, W_H / 2 + 2, color);
	my_mlx_pixel_put(img, W_W / 2 - 2, W_H / 2 - (CH_GAP * 5) - i, color);
	my_mlx_pixel_put(img, W_W / 2 - 2, W_H / 2 + (CH_GAP * 5) + i, color);
	my_mlx_pixel_put(img, W_W / 2 - 1, W_H / 2 - (CH_GAP * 5) - i, color);
	my_mlx_pixel_put(img, W_W / 2 - 1, W_H / 2 + (CH_GAP * 5) + i, color);
	my_mlx_pixel_put(img, W_W / 2 + 1, W_H / 2 - (CH_GAP * 5) - i, color);
	my_mlx_pixel_put(img, W_W / 2 + 1, W_H / 2 + (CH_GAP * 5) + i, color);
	my_mlx_pixel_put(img, W_W / 2 + 2, W_H / 2 - (CH_GAP * 5) - i, color);
	my_mlx_pixel_put(img, W_W / 2 + 2, W_H / 2 + (CH_GAP * 5) + i, color);
}

static void	draw_ch_outline_ends(t_mlx_img *img, int i, int color)
{
	my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i, W_H / 2 - 1, color);
	my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i, W_H / 2, color);
	my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i, W_H / 2 + 1, color);
	my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i - 1, W_H / 2, color);
	my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i, W_H / 2 - 1, color);
	my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i, W_H / 2, color);
	my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i, W_H / 2 + 1, color);
	my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i + 1, W_H / 2, color);
	my_mlx_pixel_put(img, W_W / 2 + 1, W_H / 2 - (CH_GAP * 5) - i, color);
	my_mlx_pixel_put(img, W_W / 2, W_H / 2 - (CH_GAP * 5) - i, color);
	my_mlx_pixel_put(img, W_W / 2 - 1, W_H / 2 - (CH_GAP * 5) - i, color);
	my_mlx_pixel_put(img, W_W / 2, W_H / 2 - (CH_GAP * 5) - i - 1, color);
	my_mlx_pixel_put(img, W_W / 2, W_H / 2 + (CH_GAP * 5) + i, color);
	my_mlx_pixel_put(img, W_W / 2 + 1, W_H / 2 + (CH_GAP * 5) + i, color);
	my_mlx_pixel_put(img, W_W / 2 - 1, W_H / 2 + (CH_GAP * 5) + i, color);
	my_mlx_pixel_put(img, W_W / 2, W_H / 2 + (CH_GAP * 5) + i + 1, color);
}

void	draw_crosshair(t_mlx_img *img)
{
	int					i;
	static unsigned int	color;

	i = -1;
	if (CH_TYPE == 1)
		color = CH_OCOLOR;
	else if (CH_TYPE == 2)
		color = CH_COLOR;
	while (++i < (double)(CH_SIZE * 10) / W_W * W_W)
	{
		my_mlx_pixel_put(img, W_W / 2 - (CH_GAP * 5) - i, W_H / 2, CH_COLOR);
		my_mlx_pixel_put(img, W_W / 2 + (CH_GAP * 5) + i, W_H / 2, CH_COLOR);
		my_mlx_pixel_put(img, W_W / 2, W_H / 2 - (CH_GAP * 5) - i, CH_COLOR);
		my_mlx_pixel_put(img, W_W / 2, W_H / 2 + (CH_GAP * 5) + i, CH_COLOR);
		if (CH_TYPE == 1)
			draw_ch_outline(img, i, color);
	}
	if (color || CH_TYPE)
		draw_ch_outline_ends(img, i, color);
}
