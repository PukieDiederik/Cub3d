/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:45:15 by drobert-          #+#    #+#             */
/*   Updated: 2023/02/08 15:36:04 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Gets magnite of vector and returns it
double	get_v_magnitude(t_vec vect)
{
	return (sqrt(powl(fabs(vect[0]), 2) + powl(fabs(vect[1]), 2)));
}

//Compares 2 vectors to 0.00001 precision
//
//Returns 0 if equal or 1 if different
int	compate_vectors(t_vec *vect1, t_vec *vect2)
{
	return ((int)(*vect1)[0] * 10000 > (int)(*vect2)[0] * 10000
			|| (int)(*vect1)[1] * 10000 > (int)(*vect2)[1] * 10000);
}

//Returns the angle between 2 vectors in degrees
double	get_angle_between_vec(t_vec	*vec1, t_vec *vec2)
{
	double	angle;

	angle = acos(get_dot_prod(vec1, vec2)
			/ (get_v_magnitude(*vec1) * get_v_magnitude(*vec2)));
	return (angle / d_to_r());
}
