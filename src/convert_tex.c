/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:29:10 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/14 00:29:12 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//loads an image by path
t_mlx_img	*load_img(char *path, t_mlx_img *img)
{
	img->img = mlx_xpm_file_to_image(*get_mlx_ptr(), path,
			&img->width, &img->height);
	return (img);
}

static t_mlx_img	*get_img_p(char *s, t_tex_info *ti)
{
	if (!ft_strncmp(s, "NO", 3))
	{
		ti->is_initialized |= 1 << 5;
		return (&ti->tex_n);
	}
	else if (!ft_strncmp(s, "SO", 3))
	{
		ti->is_initialized |= 1 << 4;
		return (&ti->tex_s);
	}
	else if (!ft_strncmp(s, "WE", 3))
	{
		ti->is_initialized |= 1 << 3;
		return (&ti->tex_w);
	}
	else if (!ft_strncmp(s, "EA", 3))
	{
		ti->is_initialized |= 1 << 2;
		return (&ti->tex_e);
	}
	return (0);
}

//Will convert string to an image or color
int	convert_tex(char **s, t_tex_info *ti)
{
	t_mlx_img	*img;
	char		*ss;

	img = get_img_p(s[0], ti);
	if (!img)
	{
		ft_putstr_fd("Error: Invalid setting name\n", 2);
		return (0);
	}
	ss = ft_substr(s[1], 0, ft_strlen(s[1]) - 1);
	load_img(ss, img);
	free(ss);
	if (!img->img)
	{
		ft_putstr_fd("Error: Could not open image\n", 2);
		return (0);
	}
	return (1);
}