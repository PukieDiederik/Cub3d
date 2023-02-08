/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:06:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/08 15:47:50 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

//DIRECTION IS A NORMALIZED VECTOR 
//TO MOVE MOVE FORWARD ADD DIRECTION VECTOR * SCALER TO PLAYER VECTOR
//POSITION VECTOR IS A VECTOR FROM MAPS (0, 0)
//ALL OTHER VECTORS HAVE POS VECTOR AS INITIAL POSITION

int	check_collision(t_vec *pos, t_vec *mov_vec, t_vars **vars)
{
	t_vec	new_pos;
	t_vec	dec_vec;
	int		i;

	i = 0;
	set_vect_to_vect(&dec_vec, mov_vec);
	scale_vect(&dec_vec, 0.25);
	add_vect(mov_vec, dec_vec);
	while (++i < 5)
	{
		sub_vect(mov_vec, dec_vec);
		set_vect_to_vect(&new_pos, pos);
		add_vect(&new_pos, *mov_vec);
		if ((*vars)->map->map[(int)new_pos[1] * (*vars)->map->width
				+ (int)new_pos[0]] != '1')
			break ;
	}
	return ((*vars)->map->map[(int)new_pos[1] * (*vars)->map->width
			+ (int)new_pos[0]] == '1');
}

void	set_width_vects(t_vec *width_dir, t_vec *width_pos
	, t_vars **vars, double angle)
{
	set_vect_to_vect(width_dir, &(*vars)->p_vec->p_dir);
	scale_vect(width_dir, 0.166);
	rotate_vec(width_dir, angle);
	set_vect_to_vect(width_pos, &(*vars)->p_vec->p_pos);
	add_vect(width_pos, *width_dir);
}

int	is_movement_coliding(t_vec *pos, t_vec *mov_vec, t_vars **vars)
{
	t_vec	check_mov_vector;
	t_vec	transf_vec;
	t_vec	width_pos;
	t_vec	width_dir;

	set_vect_to_vect(&check_mov_vector, mov_vec);
	if (check_collision(pos, &check_mov_vector, vars))
		return (1);
	set_vect_to_vect(&transf_vec, &check_mov_vector);
	set_vect_to_vect(&check_mov_vector, mov_vec);
	set_width_vects(&width_dir, &width_pos, vars, 45);
	set_vect_to_vect(&check_mov_vector, mov_vec);
	if (check_collision(&width_pos, &check_mov_vector, vars))
		return (1);
	set_width_vects(&width_dir, &width_pos, vars, -45);
	set_vect_to_vect(&check_mov_vector, mov_vec);
	if (check_collision(&width_pos, &check_mov_vector, vars))
		return (1);
	set_vect_to_vect(mov_vec, &transf_vec);
	return (0);
}

void	set_screen_vect(t_pos_v **pos)
{
	set_vect_to_vect(&(*pos)->screen, &(*pos)->p_dir);
	rotate_vec(&(*pos)->screen, 90);
	scale_vect(&(*pos)->screen, tan(fov() / 2));
}
