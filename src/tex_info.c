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

// Frees up a split string, returns 0 for easy returns
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
	t->textures[NORTH].img = 0;
	t->textures[SOUTH].img = 0;
	t->textures[EAST].img = 0;
	t->textures[WEST].img = 0;
}

// Will clean up memory for t_tex_info
void	destroy_tex_info(t_tex_info *t)
{
	if ((t->is_initialized >> 5) & 1 && t->textures[NORTH].img)
		mlx_destroy_image(*get_mlx_ptr(), t->textures[NORTH].img);
	if ((t->is_initialized >> 4) & 1 && t->textures[SOUTH].img)
		mlx_destroy_image(*get_mlx_ptr(), t->textures[SOUTH].img);
	if ((t->is_initialized >> 3) & 1 && t->textures[WEST].img)
		mlx_destroy_image(*get_mlx_ptr(), t->textures[WEST].img);
	if ((t->is_initialized >> 2) & 1 && t->textures[EAST].img)
		mlx_destroy_image(*get_mlx_ptr(), t->textures[EAST].img);
	init_tex_info(t);
}

/* set_texture_info
 *
 * Will read all the settings from a list
 * Returns the 6th element in 'f' on success, NULL on failure
 *
 * ti - The texture info to store it in
 * f - The list of strings to read from
 * NOTE: is_initialized will be 0b00111111 if everything is initialized
 */
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
