/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:53:03 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/08 15:58:04 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mov_interactions(int keycode, t_vars **vars, t_vec *s_d_v)
{
	if (keycode == 119)
	{
		if (!is_movement_coliding(&(*vars)->p_vec->p_pos, s_d_v, vars))
			add_vect(&(*vars)->p_vec->p_pos, *s_d_v);
	}
	else if (keycode == 97)
	{
		rotate_vec(s_d_v, 90);
		if (!is_movement_coliding(&(*vars)->p_vec->p_pos, s_d_v, vars))
			add_vect(&(*vars)->p_vec->p_pos, *s_d_v);
	}
	else if (keycode == 115)
	{
		rotate_vec(s_d_v, 180);
		if (!is_movement_coliding(&(*vars)->p_vec->p_pos, s_d_v, vars))
			add_vect(&(*vars)->p_vec->p_pos, *s_d_v);
	}
	else if (keycode == 100)
	{
		rotate_vec(s_d_v, 270);
		if (!is_movement_coliding(&(*vars)->p_vec->p_pos, s_d_v, vars))
			add_vect(&(*vars)->p_vec->p_pos, *s_d_v);
	}
}

int	kb_interaction(int keycode, t_vars **vars)
{
	t_vec	s_d_v;
	double	move_speed;

	move_speed = 0.1;
	set_vect_to_vect(&s_d_v, &(*vars)->p_vec->p_dir);
	scale_vect(&s_d_v, move_speed);
	if (keycode == L_ARROW)
		rotate_vec(&((*vars)->p_vec->p_dir), 2);
	else if (keycode == R_ARROW)
		rotate_vec(&((*vars)->p_vec->p_dir), -2);
	if (keycode == ESC)
		clear_exit();
	mov_interactions(keycode, vars, &s_d_v);
	cast_rays(vars);
	return (0);
}

int	mouse_aim(int x, int y, t_vars **vars)
{
	double		move_amount;

	(void)y;
	if (x - W_W / 2 > ((int)W_W / 50) || x - W_W / 2 < -((int)W_W / 50))
	{
		move_amount = -1 * MOUSE_SENS;
		if (x - W_W / 2 < 0)
			move_amount = -move_amount;
		rotate_vec(&(*vars)->p_vec->p_dir, move_amount * MOUSE_SENS);
		cast_rays(vars);
		mlx_mouse_move((*vars)->mlx, (*vars)->win, W_W / 2, W_H / 2);
	}
	return (1);
}
