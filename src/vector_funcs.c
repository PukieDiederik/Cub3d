/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:06:09 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/03 18:20:54 by leferrei         ###   ########.fr       */
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
	(*sum_vect)[0] += vect_to_add[0];
	(*sum_vect)[1] += vect_to_add[1];
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
	//printf("rotate vector called on vector %lfx %lfy\n", (*vec)[0], (*vec)[1]);
//	angle += 180;
	angle *= DEG_TO_RAD;
	x = ((*vec)[0] * cos(angle)) + ((*vec)[1] * sin(angle));
	y = ((*vec)[0] * -sin(angle)) + ((*vec)[1] * cos(angle));
	(*vec)[0] = x;
	(*vec)[1] = y;
	//printf("after rotate vector called on vector %lfx %lfy\n", *(vec)[0], (*vec)[1]);

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

int	check_collision(t_vec *pos, t_vec *mov_vec, t_vars **vars)
{
	t_vec	new_pos;
	t_vec	dec_vec;
	// int		i;
	
	// i = 0;
	set_vect_to_vect(&dec_vec, mov_vec);
	scale_vect(&dec_vec, 0.05);
	// while (++i < 20)
	// {
		sub_vect(mov_vec, dec_vec);
		set_vect_to_vect(&new_pos, pos);
		add_vect(&new_pos, *mov_vec);
		if ((*vars)->map->map[(int)new_pos[1] * (*vars)->map->width
			+ (int)new_pos[0]] == '1')
			printf("movement will collide\n");
		else if (printf("movement valid\n")){}
			// break ;
	//}
	return ((*vars)->map->map[(int)new_pos[1] * (*vars)->map->width
		+ (int)new_pos[0]] == '1');
}

int	is_movement_coliding(t_vec *pos, t_vec *mov_vec, t_vars **vars)
{
	int		result;
	t_vec	check_mov_vector;
	t_vec	transf_vec;
	
	set_vect_to_vect(&check_mov_vector, mov_vec);
	result = check_collision(pos, &check_mov_vector, vars);
	set_vect_to_vect(&transf_vec, &check_mov_vector);
	set_vect_to_vect(&check_mov_vector, mov_vec);
	if (result)
		return (result);
	rotate_vec(&check_mov_vector, FOV_DEG / 2);
	result = check_collision(pos, &check_mov_vector, vars);
	set_vect_to_vect(&check_mov_vector, mov_vec);
	if (result)
		return (result);	
	rotate_vec(&check_mov_vector, FOV_DEG / 2);
	result = check_collision(pos, &check_mov_vector, vars);
	if (result)
		return (result);	
	rotate_vec(mov_vec, 25);
	set_vect_to_vect(mov_vec, &transf_vec);
	return (0);
}

void	normalize_vector(t_vec	*vec)
{
	double	m = get_v_magnitude(*vec);
	(*vec)[0] = (*vec)[0] / m;
	(*vec)[1] = (*vec)[1] / m;
}

void	set_screen_vect(t_pos_v **pos)
{
	set_vect_to_vect(&(*pos)->screen, &(*pos)->p_dir);
//	printf("before rotate = (%lf, %lf)\n", pos->screen[0], pos->screen[1]);
	rotate_vec(&(*pos)->screen, 90);
//	printf("after rotate = (%lf, %lf)\n", pos->screen[0], pos->screen[1]);
	scale_vect(&(*pos)->screen, tan(FOV / 2));
}

