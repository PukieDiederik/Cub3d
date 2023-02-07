/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:37:31 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/07 18:00:53 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline double	mm_spacer(void)
{
	return ((double)mm_s()  / ((double)MM_SPACER_SCALE / W_W * W_W));
}

inline double	mm_b_s(void)
{
	return ((double)mm_s() / 20);
}

inline double	fov(void)
{
	return (((double)FOV_DEG * d_to_r()));
}

inline int	mm_s(void)
{
	return ((int)((double)W_W / (double)MM_SCALE));
}

inline double	d_to_r(void)
{
	return (M_PI / 180.0);
}