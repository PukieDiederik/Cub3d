/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:12:48 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/14 00:12:51 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

static void	*clear_split(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		free(s[i]);
		++i;
	}
	free(s);
	return (0);
}

// Initializes tex_info with empty values
void	init_tex_info(t_tex_info *t)
{
	t->is_initialized = 0;
	t->ceiling_color = 0;
	t->floor_color = 0;
	t->tex_n.img = 0;
	t->tex_s.img = 0;
	t->tex_e.img = 0;
	t->tex_w.img = 0;
}

void	destroy_tex_info(t_tex_info *t)
{
	if ((t->is_initialized >> 5) & 1 && t->tex_n.img)
		mlx_destroy_image(*get_mlx_ptr(), t->tex_n.img);
	if ((t->is_initialized >> 4) & 1 && t->tex_s.img)
		mlx_destroy_image(*get_mlx_ptr(), t->tex_s.img);
	if ((t->is_initialized >> 3) & 1 && t->tex_w.img)
		mlx_destroy_image(*get_mlx_ptr(), t->tex_w.img);
	if ((t->is_initialized >> 2) & 1 && t->tex_e.img)
		mlx_destroy_image(*get_mlx_ptr(), t->tex_e.img);
	t->tex_n.img = 0;
	t->tex_s.img = 0;
	t->tex_e.img = 0;
	t->tex_w.img = 0;
	t->is_initialized = 0;
}

// Will return the start of the map on success
// Will return NULL if there was an issue
// is_initialized will be 00111111b if everything is initialized
t_list	*set_texture_info(t_tex_info *ti, t_list *f)
{
	int		i;
	char	**s_str;

	i = -1;
	while (++i < 6 && f)
	{
		s_str = ft_split((char *)f->content, ' ');
		if (!s_str || !s_str[0] || !s_str[1] || s_str[2])
		{
			ft_putstr_fd("Error: while parsing settings\n", 2);
			return (clear_split(s_str));
		}
		if ((s_str[0][1] && !convert_tex(s_str, ti))
			|| (!s_str[0][1] && !convert_color(s_str, ti)))
			return (clear_split(s_str));
		clear_split(s_str);
		f = f->next;
	}
	return (f);
}
