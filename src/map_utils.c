/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:17:06 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/13 18:17:08 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

// Frees up memory used by map, does not actually free map itself
void	destroy_map(t_map *m)
{
	if (!m)
		return ;
	free(m->map);
	m->map = 0;
	m->width = 0;
	m->height = 0;
}
