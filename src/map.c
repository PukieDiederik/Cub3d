/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:32:26 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/13 17:32:29 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int		is_map_enclosed(t_map *m);

// Checks if a line contains invalid characters,
// and sets if a player has been found
static int	is_valid_line(char *l, int *found_player)
{
	int	i;

	i = 0;
	while (l[i] && l[i] != '\n')
	{
		if (l[i] != ' ' && l[i] != '0' && l[i] != '1'
			&& !is_player_char(l[i]))
			return (-1);
		if (is_player_char(l[i]))
		{
			if (*found_player)
			{
				ft_putstr_fd("Error: Multiple players\n", 2);
				return (-1);
			}
			*found_player = 1;
		}
		++i;
	}
	return (i);
}

// Sets the map size and checks if there are invalid characters
static int	set_map_size(t_map *m, t_list *l, int found_player)
{
	int	max_width;
	int	length;
	int	len;

	found_player = 0;
	length = 0;
	max_width = 0;
	while (l)
	{
		len = is_valid_line((char *)l->content, &found_player);
		if (len < 0)
			return (0);
		if (len > max_width)
			max_width = len;
		l = l->next;
		++length;
	}
	if (!found_player)
	{
		ft_putstr_fd("Error: No player found\n", 2);
		return (0);
	}
	m->width = max_width;
	m->height = length;
	return (1);
}

// Sets the player when its found
void	set_player(t_map *m, int x, int y, char f)
{
	m->map[y * m->width + x] = '0';
	m->player_spawn_x = x;
	m->player_spawn_y = y;
	m->player_facing = f;
}

// Writes the list of strings into the map
static void	populate_map(t_map *m, t_list *l)
{
	char	*line;
	int		read_line;
	int		y;
	int		x;

	y = -1;
	while (++y < m->height)
	{
		line = (char *)(l->content);
		read_line = 0;
		x = -1;
		while (++x < m->width)
		{
			if (!read_line && (line[x] == '\0' || line[x] == '\n'))
				read_line = 1;
			if (!read_line && is_player_char(line[x]))
				set_player(m, x, y, line[x]);
			else if (!read_line)
				m->map[y * m->width + x] = line[x];
			else
				m->map[y * m->width + x] = ' ';
		}
		l = l->next;
	}
}

/* get_map
 *
 * Creates a map object from a list of strings
 * Returns a t_map* if it is a valid map, NULL on an invalid map
 *
 * l - the list of strings
 */
t_map	*get_map(t_list *l)
{
	t_map	*m;

	m = malloc(sizeof(t_map));
	if (!m || !set_map_size(m, l, 0) || m->width < 3 || m->height < 3)
	{
		free(m);
		return (0);
	}
	m->map = malloc(m->width * m->height * sizeof(char));
	if (!m->map)
	{
		ft_putstr_fd("Error: couldn't allocate memory\n", 2);
		free(m);
		return (0);
	}
	populate_map(m, l);
	if (!is_map_enclosed(m))
	{
		ft_putstr_fd("Error: map is not enclosed\n", 2);
		destroy_map(m);
		free (m);
		return (0);
	}
	return (m);
}
