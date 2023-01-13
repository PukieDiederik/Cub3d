/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:16:57 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/13 18:16:58 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	print_map(t_map *m)
{
	int	i;
	int	s;
	int	pp;

	printf("Map size: (%d,%d)\n", m->width, m->height);
	printf("Player Position: (%d,%d)\n",
		m->player_spawn_x, m->player_spawn_y);
	i = 0;
	s = m->width * m->height;
	pp = m->player_spawn_x + m->width * m->player_spawn_y;
	while (i < s)
	{
		if (i == pp)
			printf("%c", m->player_facing);
		else
			(printf("%c", m->map[i]));
		++i;
		if (!(i % m->width) && i < s - 1)
			printf("\n");
	}
	printf("\n");
}
