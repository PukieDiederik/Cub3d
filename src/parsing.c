/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:31:19 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/13 23:31:20 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"

// This function will return a t_map (allocated)
// object with the correct with, height and map.
// minimum amount of lines required is 6 (settings) + 3(minimum map size) = 9
t_map	*parse_map(char *file, t_tex_info *ti)
{
	int		fd;
	t_list	*l;
	t_map	*m;

	init_tex_info(ti);
	fd = get_map_fd(file);
	if (fd < 0)
		return (0);
	l = read_map(fd);
	if (ft_lstsize(l) <= 9)
	{
		ft_lstclear(&l, free);
		return (0);
	}
	if (!set_texture_info(ti, l))
		return (0);
	m = get_map(l->next->next->next->next->next->next);
	ft_lstclear(&l, free);
	close(fd);
	return (m);
}
