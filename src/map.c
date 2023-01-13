#include "cub3d.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void print_map(t_map* m)
{
	int	i;
	int	s;
	int pp;

	printf("Map size: (%d,%d)\n", m->width, m->height);
	printf("Player Position: (%d,%d)\n", m->player_spawn_x, m->player_spawn_y);
	i = 0;
	s = m->width * m->height;
	pp = m->player_spawn_x + m->width * m->player_spawn_y;
	while(i < s)
	{
		if (i == pp)
			printf("%c", m->player_facing);
		else
			(printf("%c", m->map[i]));
		++i;
		if (!(i % m->width) && i < s - 1)
			printf("\n");
	}
}

static int is_valid_line (char *l, int *found_player)
{
	int	i;

	i = 0;
	while(l[i] && l[i] != '\n')
	{
		if (l[i] != ' ' && l[i] != '0' && l[i] != '1' && l[i] != 'N' && l[i] != 'S'
			&& l[i] != 'E' && l[i] != 'W')
			return (-1);
		if (l[i] == 'N' || l[i] == 'S' || l[i] == 'E' || l[i] == 'W')
		{
			if (*found_player)
				return (-1);
			*found_player = 1;
		}
		++i;
	}
	return (i);
}

void destroy_map(t_map *m)
{
	free(m->map);
	m->map = 0;
	m->width = 0;
	m->height = 0;
}

// Sets the map size and
int set_map_size(t_map *m, t_list *l)
{
	int found_player;
	int max_width;
	int length;
	int len;

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
		return (0);
	m->width = max_width;
	m->height = length;
	return (1);
}

int pos_to_index (int width, int x, int y)
{
	return (y * width + x);
}

int is_map_enclosed(t_map *m)
{
	int	x;
	int	y;

	y = 0;
	while (++y < m->height - 1)
	{
		x = 0;
		while (++x < m->width - 1)
			if (m->map[pos_to_index(m->width, x, y)] == '0'
				&& (m->map[pos_to_index(m->width, x - 1, y)] == ' '
				|| m->map[pos_to_index(m->width, x - 1, y - 1)] == ' '
				|| m->map[pos_to_index(m->width, x - 1, y + 1)] == ' '
				|| m->map[pos_to_index(m->width, x + 1, y - 1)] == ' '
				|| m->map[pos_to_index(m->width, x + 1, y)] == ' '
				|| m->map[pos_to_index(m->width, x + 1, y + 1)] == ' '
				|| m->map[pos_to_index(m->width, x, y + 1)] == ' '
				|| m->map[pos_to_index(m->width, x, y - 1)] == ' '))
				return (0);
		++y;
	}
	return (1);
}

t_map *get_map(t_list *l)
{
	t_map	*m;
	int		x;
	int		y;
	int		read_line;

	m = malloc(sizeof(t_map));
	if (!set_map_size(m, l))
		return (0);
	m->map = malloc(m->width * m->height * sizeof(char));
	y = 0;
	while (y < m->height)
	{
		read_line = 0;
		x = 0;
		while (x < m->width)
		{
			if (!*(char *)(l->content))
				read_line = 1;
			if (!read_line && (((char *)(l->content))[x] == 'N'
				|| ((char *)(l->content))[x] == 'S'
				|| ((char *)(l->content))[x] == 'E'
				|| ((char *)(l->content))[x] == 'W'))
			{
				m->map[y * m->width + x] = '0';
				m->player_spawn_x = x;
				m->player_spawn_y = y;
				m->player_facing = ((char *)(l->content))[x];
			}
			else if (!read_line)
				m->map[y * m->width + x] = ((char *)(l->content))[x];
			else
				m->map[y * m->width + x] = ' ';
			x++;
		}
		l = l->next;
		y++;
	}
	if (!is_map_enclosed(m))
	{
		destroy_map(m);
		free (m);
		return (0);
	}
	return (m);
}