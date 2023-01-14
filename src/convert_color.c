/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:59:12 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/13 23:59:14 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

//Converts the string to a number
int	conv_col_num(char *start, char **end)
{
	int		num;
	char	*new_end;

	if (!ft_isdigit(start[0]))
		return (-1);
	num = start[0] - '0';
	new_end = start + 1;
	if (ft_isdigit(start[1]))
	{
		num = num * 10 + start[1] - '0';
		new_end = start + 2;
		if (ft_isdigit(start[2]))
		{
			num = num * 10 + start[2] - '0';
			new_end = start + 3;
		}
	}
	if (num > 255)
		return (-1);
	*end = new_end;
	return (num);
}

int	set_col(char **s, t_tex_info *ti, int col)
{
	if (s[0][0] == 'C')
	{
		ti->ceiling_color = col;
		ti->is_initialized |= 1;
	}
	else if (s[0][0] == 'F')
	{
		ti->floor_color = col;
		ti->is_initialized |= 1 << 1;
	}
	else
	{
		ft_putstr_fd("Error: Invalid setting name\n", 2);
		return (0);
	}
	return (1);
}

int	convert_color(char **s, t_tex_info *ti)
{
	int		r;
	int		g;
	int		b;
	char	*end;
	int		err;

	err = 0;
	r = conv_col_num(s[1], &end);
	if (*end != ',')
		err = 1;
	g = conv_col_num(end + 1, &end);
	if (*end != ',')
		err = 1;
	b = conv_col_num(end + 1, &end);
	if (err || r < 0 || g < 0 || b < 0 || *end != '\n')
	{
		ft_putstr_fd("Error: Could not convert color\n", 2);
		return (0);
	}
	return (set_col(s, ti, (r << 16) | (g << 8) | (b)));
}