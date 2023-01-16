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

// Converts the string to a number
static int	conv_col_num(char *start, char **end)
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
	*end = new_end;
	if (num > 255)
		return (-1);
	return (num);
}

// Sets the correct color in t_tex_info
static int	set_col(char **s, t_tex_info *ti, int col)
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

/* convert_color
 *
 * Converts a split string into a color formatted inside an int
 * Returns 1 on success, 0 on failure
 *
 * s - The split string
 *     (s[0] should be the identifier, s[1] should be the value)
 * ti - The place all texture info is stored
 */
int	convert_color(char **s, t_tex_info *ti)
{
	int		r;
	int		g;
	int		b;
	char	*end;
	int		err;

	err = 0;
	r = conv_col_num(s[1], &end);
	if (r < 0 || *end != ',')
		err = 1;
	if (!err)
	{
		g = conv_col_num(end + 1, &end);
		if (g < 0 || *end != ',')
			err = 1;
		else
			b = conv_col_num(end + 1, &end);
	}
	if (err || b < 0 || *end != '\n')
	{
		ft_putstr_fd("Error: Could not convert color\n", 2);
		return (0);
	}
	return (set_col(s, ti, (r << 16) | (g << 8) | (b)));
}
