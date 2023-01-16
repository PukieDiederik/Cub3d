/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:38:44 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/13 23:38:46 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

/* read_map
 *
 * Will read the map and store it in a linked list of strings
 *
 * fd - the file descriptor to read from
 *
 * NOTE: It will skip empty lines for the first 6 lines. This will make it
 * so the first 6 lines will always be the settings
 */
t_list	*read_map(int fd)
{
	t_list	*tmp;
	t_list	*ret;
	char	*line;

	ret = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_lstsize(ret) < 7 && (!line[0] || line[0] == '\n'))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			ft_lstclear(&tmp, free);
			return (0);
		}
		ft_lstadd_back(&ret, tmp);
		line = get_next_line(fd);
	}
	return (ret);
}

// will open a map file or return -1 on error;
int	get_map_fd(char *file)
{
	size_t	len;
	int		fd;

	len = ft_strlen(file);
	if (len < 4 || file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
	{
		ft_putstr_fd("Error: Invalid map name\n", 2);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("Error: Could not open file\n", 2);
	return (fd);
}
