/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:06:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/01 17:55:57 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

//DIRECTION IS A NORMALIZED VECTOR 
//TO MOVE MOVE FORWARD ADD DIRECTION VECTOR * SCALER TO PLAYER VECTOR
//POSITION VECTOR IS A VECTOR FROM MAPS (0, 0)
//ALL OTHER VECTORS HAVE POS VECTOR AS INITIAL POSITION
double	get_v_magnitude(t_vec vect)
{
	return (sqrt(
		powl(fabs(vect[0]), 2) +
		powl(fabs(vect[1]), 2)
		));
}

void	add_vect(t_vec *sum_vect, t_vec vect_to_add)
{
	(*sum_vect)[0] = (*sum_vect[0]) * vect_to_add[0];
	(*sum_vect)[1] = (*sum_vect[1]) * vect_to_add[1];
}

void	sub_vect(t_vec *sub_vect, t_vec vect_to_sub)
{
	(*sub_vect)[0] = (*sub_vect)[0] - vect_to_sub[0];
	(*sub_vect)[1] = (*sub_vect)[1] - vect_to_sub[1];
}

void	rotate_vec(t_vec *vec, double angle)
{
	double	x;
	double	y;
	angle += 180;
	angle *= DEG_TO_RAD;
	x = ((*vec)[0] * cos(angle)) + ((*vec)[1] * sin(angle));
	y = ((*vec)[0] * -sin(angle)) + ((*vec)[1] * cos(angle));
	(*vec)[0] = x;
	(*vec)[1] = y;
}

// t_vec	*return_rot_vec(t_vec *vec, double angle)
// {
// 	double	hyp
// }
void	scale_vect(t_vec *vect, double scale)
{
	(*vect)[0] *= scale;
	(*vect)[1] *= scale;
}

int	compate_vectors(t_vec *vect1, t_vec *vect2)
{
	return ((*vect1)[0] != (*vect2)[0] || (*vect1)[1] != (*vect2)[1]);
}

void	set_vect_to_vect(t_vec *vect_to_set, t_vec *vect_to_get)
{
	(*vect_to_set)[0] = (*vect_to_get)[0];
	(*vect_to_set)[1] = (*vect_to_get)[1];

}

void	set_screen_vect(t_pos_v *pos)
{
	pos->screen[0] = pos->p_dir[0];
	pos->screen[1] = pos->p_dir[1];
	printf("before rotate = (%lf, %lf)\n", pos->screen[0], pos->screen[1]);
	rotate_vec(&pos->screen, 90);
	printf("after rotate = (%lf, %lf)\n", pos->screen[0], pos->screen[1]);
	scale_vect(&pos->screen, tan(FOV / 2));
}

