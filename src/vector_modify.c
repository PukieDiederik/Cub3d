/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_modify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:47:09 by drobert-          #+#    #+#             */
/*   Updated: 2023/02/07 18:47:10 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Rotates vector in place - !changes vector values!
void	rotate_vec(t_vec *vec, double angle)
{
	double	x;
	double	y;

	angle *= d_to_r();
	x = ((*vec)[0] * cos(angle)) + ((*vec)[1] * sin(angle));
	y = ((*vec)[0] * -sin(angle)) + ((*vec)[1] * cos(angle));
	(*vec)[0] = x;
	(*vec)[1] = y;
}

//Sets values of vect_to_set to values of vect_to_get
//
//!Changes vector values!
void	set_vect_to_vect(t_vec *vect_to_set, t_vec *vect_to_get)
{
	(*vect_to_set)[0] = (*vect_to_get)[0];
	(*vect_to_set)[1] = (*vect_to_get)[1];
}
