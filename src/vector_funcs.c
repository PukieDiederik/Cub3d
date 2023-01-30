/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:06:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/01/30 17:41:48 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

//DIRECTION IS A NORMALIZED VECTOR 
//TO MOVE MOVE FORWARD ADD DIRECTION VECTOR * SCALER TO PLAYER VECTOR
//POSITION VECTOR IS A VECTOR FROM MAPS (0, 0)
//ALL OTHER VECTORS HAVE POS VECTOR AS INITIAL POSITION
double	get_v_magnitude(t_vect *vect)
{
	return (sqrt(
		powl((fabs(vect->terminal_x_y[0] - vect->initial_x_y[0])), 2) +
		powl((fabs(vect->terminal_x_y[1] - vect->initial_x_y[1])), 2)
		));
}

double	get_v_direction(t_vect *vect)
{

}

t_vect	*scale_vect(t_vect *vect, double scale)
{
	t_vect	*vecto;
	
	if (!vecto)
		return (0);
	vecto->terminal_x_y[0] = scale * vect->terminal_x_y[0];
	vecto->terminal_x_y[1] = scale * vect->terminal_x_y[1];

	
}