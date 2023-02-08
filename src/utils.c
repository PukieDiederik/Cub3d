/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:55:14 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/08 15:55:25 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	b_putstr_fd(char *str, int fd)
{
	int	d;

	d = write(fd, str, ft_strlen(str));
	(void)d;
	return (0);
}

t_vars	**get_vars(void)
{
	static t_vars	*vars;

	return (&vars);
}

void	**get_mlx_ptr(void)
{
	return (&(*get_vars())->mlx);
}

int	clear_exit(void)
{
	destroy_map((*get_vars())->map);
	free((*get_vars())->map);
	destroy_tex_info(&(*get_vars())->tex_info);
	mlx_destroy_image((*get_vars())->mlx, (*get_vars())->render_buffer.img);
	mlx_destroy_window((*get_vars())->mlx, (*get_vars())->win);
	mlx_destroy_display((*get_vars())->mlx);
	free((*get_vars())->mlx);
	free((*get_vars())->p_vec);
	free((*get_vars()));
	exit(0);
}

int	are_options_valid(void)
{
	if (mm_s() + mm_b_s() * 2 + mm_spacer() > W_W
		|| mm_s() + mm_b_s() * 2 + mm_spacer() < 0
		|| mm_s() + mm_b_s() * 2 + mm_spacer() > W_W
		|| mm_s() + mm_b_s() * 2 + mm_spacer() < 0)
		return (0);
	if (MOUSE_SENS < 0 || CH_TYPE < 0 || CH_TYPE > 2
		|| W_W / 2 - ((double)(CH_SIZE * 10) / W_W * W_W) - (CH_GAP * 5) - 1 < 0
		|| W_H / 2 - ((double)(CH_SIZE * 10) / W_W * W_W) - (CH_GAP * 5) - 1 < 0
		|| ((double)(CH_SIZE * 10) / W_W * W_W) + (CH_GAP * 5) > W_H / 2 - 1
		|| ((double)(CH_SIZE * 10) / W_W * W_W) + (CH_GAP * 5) > W_W / 2 - 1)
		return (0);
	return (1);
}
