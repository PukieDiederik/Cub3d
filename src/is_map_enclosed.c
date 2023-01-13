/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_enclosed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:59:24 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/13 17:59:25 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	pos_to_index(int width, int x, int y)
{
	return (y * width + x);
}

static int	check_around(t_map *m, int x, int y)
{
	return (m->map[pos_to_index(m->width, x - 1, y)] == ' '
		|| m->map[pos_to_index(m->width, x - 1, y - 1)] == ' '
		|| m->map[pos_to_index(m->width, x - 1, y + 1)] == ' '
		|| m->map[pos_to_index(m->width, x + 1, y - 1)] == ' '
		|| m->map[pos_to_index(m->width, x + 1, y)] == ' '
		|| m->map[pos_to_index(m->width, x + 1, y + 1)] == ' '
		|| m->map[pos_to_index(m->width, x, y + 1)] == ' '
		|| m->map[pos_to_index(m->width, x, y - 1)] == ' ');
}

int	is_map_enclosed(t_map *m)
{
	int	x;
	int	y;

	y = 0;
	while (++y < m->height - 1)
	{
		x = 0;
		while (++x < m->width - 1)
			if (m->map[pos_to_index(m->width, x, y)] == '0'
				&& check_around(m, x, y))
				return (0);
		++y;
	}
	x = -1;
	while (++x < m->height)
		if (m->map[pos_to_index(m->width, 0, x)] == '0'
			|| m->map[pos_to_index(m->width, m->width - 1, x)] == '0'
			|| m->map[pos_to_index(m->width, x, 0)] == '0'
			|| m->map[pos_to_index(m->width, x, m->height - 1)] == '0')
			return (0);
	return (1);
}
