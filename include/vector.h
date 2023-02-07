/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:18:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/07 17:21:16 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

//Type defs
typedef double	t_vec[2];

//Constants
# define DEG_TO_RAD (M_PI / 180.0)

//Functions
void	add_vect(t_vec *sum_vect, t_vec vect_to_add);
void	scale_vect(t_vec *vect, double scale);
double	get_v_magnitude(t_vec vect);
void	rotate_vec(t_vec *vec, double angle);
int		compate_vectors(t_vec *vect1, t_vec *vect2);
void	set_vect_to_vect(t_vec *vect_to_set, t_vec *vect_to_get);
void	normalize_vector(t_vec	*vec);
double	get_angle_between_vec(t_vec	*vec1, t_vec *vec2);

#endif
