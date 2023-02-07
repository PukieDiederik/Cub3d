/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:43:25 by drobert-          #+#    #+#             */
/*   Updated: 2023/02/07 18:43:26 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Sums values of both vectors into sum_vect - !changes vector values!
void	add_vect(t_vec *sum_vect, t_vec vect_to_add)
{
	(*sum_vect)[0] += vect_to_add[0];
	(*sum_vect)[1] += vect_to_add[1];
}

//Subtracts values of both vectors into sub_vect - !changes vector values!
void	sub_vect(t_vec *sub_vect, t_vec vect_to_sub)
{
	(*sub_vect)[0] = (*sub_vect)[0] - vect_to_sub[0];
	(*sub_vect)[1] = (*sub_vect)[1] - vect_to_sub[1];
}

int	get_dot_prod(t_vec *vec1, t_vec *vec2)
{
	return ((*vec1)[0] * (*vec2)[0] + (*vec1)[1] * (*vec2)[1]);
}

//Normalizes vector to magnitude of 1 - !changes vector values!
void	normalize_vector(t_vec	*vec)
{
	double	m;

	m = get_v_magnitude(*vec);
	(*vec)[0] = (*vec)[0] / m;
	(*vec)[1] = (*vec)[1] / m;
}

//Scales vector in place - !changes vector values!
void	scale_vect(t_vec *vect, double scale)
{
	(*vect)[0] *= scale;
	(*vect)[1] *= scale;
}
