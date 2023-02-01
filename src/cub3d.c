/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:14:14 by drobert-          #+#    #+#             */
/*   Updated: 2023/02/01 18:01:56 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "libft.h"
#include <stdio.h>

int	b_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	return (0);
}

t_vars **get_vars(void)
{
	static t_vars	*vars;
	
	return (&vars);
}

void	**get_mlx_ptr(void)
{
	return (&(*get_vars())->mlx);
}

int	clear_exit()
{
	destroy_map((*get_vars())->map);
	free((*get_vars())->map);
	destroy_tex_info(&(*get_vars())->tex_info);
	mlx_destroy_image((*get_vars())->mlx, (*get_vars())->render_buffer.img);
	mlx_destroy_window((*get_vars())->mlx, (*get_vars())->win);
	mlx_destroy_display((*get_vars())->mlx);
	free((*get_vars())->mlx);
	exit(0);

}

int	kb_interaction(int keycode, t_vars *vars)
{
	// if (keycode == L_ARROW)
	// 	rotate_vec(&vars->p_vec.p_dir, 360 - 0.5);
	// if (keycode == R_ARROW)
	// 	rotate_vec(&vars->p_vec.p_dir, 0.5);
	(void)vars;
	printf("keycode = %d\n", keycode);
	return (0);
}

int	init_window()
{
	(*get_vars())->win = mlx_new_window((*get_vars())->mlx,
		WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	(*get_vars())->render_buffer.img = mlx_new_image((*get_vars())->mlx, WIN_WIDTH, WIN_HEIGHT);
	(*get_vars())->render_buffer.addr = mlx_get_data_addr((*get_vars())->render_buffer.img,
	&(*get_vars())->render_buffer.bits_per_pixel, &(*get_vars())->render_buffer.line_length,
	&(*get_vars())->render_buffer.endian);
	mlx_put_image_to_window((*get_vars())->mlx, (*get_vars())->win, (*get_vars())->render_buffer.img, 0, 0);
	set_starting_pdata(&(*get_vars())->p_vec, 0);
	
	mlx_hook((*get_vars())->win, ON_DESTROY, 0, &clear_exit, get_vars());
	mlx_loop_hook((*get_vars())->mlx, cast_rays, *get_vars());
	mlx_key_hook((*get_vars()), &kb_interaction, *get_vars());
	mlx_do_key_autorepeaton((*get_vars())->mlx);
	mlx_loop((*get_vars())->mlx);
	return (1);

}

int	main(int argc, char **argv)
{
	*get_vars() = malloc(sizeof(t_vars));
	if (argc != 2 || !*get_vars())
		return (b_putstr_fd("Error: Could not init\n", STDERR_FILENO) + 1);
	// Initializes our MLX
	*get_mlx_ptr() = mlx_init();
	if (!*get_mlx_ptr())
		return (b_putstr_fd("Error: MLX error\n", STDERR_FILENO) + 1);
	// map will be a valid pointer on success, if any error this will be NULL
	(*get_vars())->map = parse_map(argv[1], &(*get_vars())->tex_info);
	if (!(*get_vars())->map)
		return (b_putstr_fd("Error: Map error\n", STDERR_FILENO) + 1);
	print_map((*get_vars())->map);
	//TODO: Raycasting & setting up MLX (hooks, window, etc...)
	init_window();
	// These are cleanup functions.
}
