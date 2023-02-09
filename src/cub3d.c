/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:14:14 by drobert-          #+#    #+#             */
/*   Updated: 2023/02/08 15:55:10 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "libft.h"
#include <stdio.h>

int	init_window(void)
{
	t_vars	**vars;

	vars = get_vars();
	(*vars)->win = mlx_new_window((*vars)->mlx, W_W, W_H, "Cub3d");
	(*vars)->render_buffer.img = mlx_new_image((*vars)->mlx, W_W, W_H);
	(*vars)->render_buffer.addr = mlx_get_data_addr((*vars)->render_buffer.img,
			&(*vars)->render_buffer.bits_per_pixel,
			&(*vars)->render_buffer.line_length,
			&(*vars)->render_buffer.endian);
	if (!set_starting_pdata(get_vars())
		&& printf("Error in init data or FOV outside of range 1-179\n"))
		return (0);
	mlx_mouse_hide((*vars)->mlx, (*vars)->win);
	cast_rays(get_vars());
	mlx_hook((*vars)->win, 6, (1L << 6), &mouse_aim, vars);
	mlx_hook((*vars)->win, ON_DESTROY, 0, &clear_exit, vars);
	mlx_hook((*vars)->win, ON_KEYDOWN, (1L << 0), &kb_interaction, vars);
	mlx_loop((*vars)->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	if (!are_options_valid())
		return (0);
	*get_vars() = malloc(sizeof(t_vars));
	if (argc != 2 || !*get_vars())
		return (b_putstr_fd("Error: Could not init\n", STDERR_FILENO) + 1);
	*get_mlx_ptr() = mlx_init();
	if (!*get_mlx_ptr())
		return (b_putstr_fd("Error: MLX error\n", STDERR_FILENO) + 1);
	(*get_vars())->map = parse_map(argv[1], &(*get_vars())->tex_info);
	if (!(*get_vars())->map)
		return (b_putstr_fd("Error: Map error\n", STDERR_FILENO) + 1);
	init_window();
}
