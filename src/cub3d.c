/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:14:14 by drobert-          #+#    #+#             */
/*   Updated: 2023/02/04 16:22:14 by leferrei         ###   ########.fr       */
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
	free((*get_vars())->p_vec);
	free((*get_vars()));
	exit(0);

}

void	draw_minimap(t_vars **vars)
{
	int	x;
	int	y;
	// double xf;
	// double yf;

	x = -1;
	(void)vars;
	while (++x < MM_HEIGHT)
	{
		y = -1;
		while (++y < MM_HEIGHT)
		{
			// yf = y;
			// xf = x;
			// yf = (yf / MM_HEIGHT) * (((*vars)->map->height - 1)) * (*vars)->map->width;
			// xf = (xf / MM_WIDTH) * ((*vars)->map->width);
			// printf("map size = %lu\n %d y %d x\n", ft_strlen((*vars)->map->map), (int)yf, (int)xf);
			if ((*vars)->map->map[4] == '1')
				my_mlx_pixel_put(&(*vars)->render_buffer, x + 10, y + 10, 0xFFFFFF);
		}
	}
}

int	kb_interaction(int keycode, t_vars **vars)
{
	t_vec	scaled_dir_vec;
	double	move_speed;

	move_speed = 0.1;
	set_vect_to_vect(&scaled_dir_vec, &(*vars)->p_vec->p_dir);
	scale_vect(&scaled_dir_vec, move_speed);
	// printf("direction vector in kb interation = %lfx %lfy - scaled %lfx %lfx\n",
		//  (*vars)->p_vec->p_dir[0], (*vars)->p_vec->p_dir[1], scaled_dir_vec[0], scaled_dir_vec[1]);
	if (keycode == L_ARROW)
		rotate_vec(&((*vars)->p_vec->p_dir), 2);
	else if (keycode == R_ARROW)
		rotate_vec(&((*vars)->p_vec->p_dir), -2);
	if (keycode == ESC)
		clear_exit();
	if (keycode == 119)
	{
		if (!is_movement_coliding(&(*vars)->p_vec->p_pos, &scaled_dir_vec, vars))
			add_vect(&(*vars)->p_vec->p_pos, scaled_dir_vec);
	}
	else if (keycode == 97)
	{
		rotate_vec(&scaled_dir_vec, 90);
		if (!is_movement_coliding(&(*vars)->p_vec->p_pos, &scaled_dir_vec, vars))
			add_vect(&(*vars)->p_vec->p_pos, scaled_dir_vec);
	}
	else if (keycode == 115)
	{
		rotate_vec(&scaled_dir_vec, 180);
		if (!is_movement_coliding(&(*vars)->p_vec->p_pos, &scaled_dir_vec, vars))
			add_vect(&(*vars)->p_vec->p_pos, scaled_dir_vec);
	}
	else if (keycode == 100)
	{
		rotate_vec(&scaled_dir_vec, 270);
		if (!is_movement_coliding(&(*vars)->p_vec->p_pos, &scaled_dir_vec, vars))
			add_vect(&(*vars)->p_vec->p_pos, scaled_dir_vec);
	}
	// printf("rotated scaled to add %lfx %lfx\n", scaled_dir_vec[0], scaled_dir_vec[1]);
	// printf("final position vector in kb interaction %lfx %lfx\n", (*vars)->p_vec->p_pos[0], (*vars)->p_vec->p_pos[1]);

	cast_rays(vars);
	//printf("keycode = %d\n\n", keycode);
	return (0);
}

int	mouse_aim(int x, int y, t_vars **vars)
{
	static int	prev_mouse_x;
	static int	step_checker;
	double		move_ammount;

	(void)y;
	if (!prev_mouse_x)
	{
		prev_mouse_x = x;
		step_checker = x;
	}
	if (prev_mouse_x - step_checker > MOUSE_AIM_STEPS
		|| prev_mouse_x - step_checker < -MOUSE_AIM_STEPS)
	{
		step_checker = prev_mouse_x;
		move_ammount = 5 * MOUSE_SENS;
		if (prev_mouse_x - x < 0)
			move_ammount = -move_ammount;
		rotate_vec(&(*vars)->p_vec->p_dir, move_ammount * MOUSE_SENS);	
		cast_rays(vars);
	}
	prev_mouse_x = x;
	return (1);
}

int	init_window()
{
	t_vars		**vars = get_vars();

	(*vars)->win = mlx_new_window((*vars)->mlx,
		W_W, W_H, "Cub3d");
	(*vars)->render_buffer.img = mlx_new_image((*vars)->mlx, W_W, W_H);
	(*vars)->render_buffer.addr = mlx_get_data_addr((*vars)->render_buffer.img,
	&(*vars)->render_buffer.bits_per_pixel, &(*vars)->render_buffer.line_length,
	&(*vars)->render_buffer.endian);
	//mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->render_buffer.img, 0, 0);
	if (!set_starting_pdata(get_vars())
		&& printf("Error in init data or FOV outside of range 1-179\n"))
		return (0);
	cast_rays(get_vars());
	//draw_minimap(get_vars());
	mlx_hook((*vars)->win, ON_DESTROY, 0, &clear_exit, vars);
	mlx_hook((*vars)->win, 6, (1L<<6) ,&mouse_aim, vars);
	mlx_hook((*vars)->win, ON_KEYDOWN, (1L << 0), &kb_interaction, vars);
	mlx_loop((*vars)->mlx);
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
	//print_map((*get_vars())->map);
	//TODO: Raycasting & setting up MLX (hooks, window, etc...)
	init_window();
	// These are cleanup functions.
}
