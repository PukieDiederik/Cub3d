/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:07:04 by drobert-          #+#    #+#             */
/*   Updated: 2022/12/28 14:07:07 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>

// STRUCTURES
/* struct s_mlx_img
 * All information required to work with an mlx image
 *
 * width, height: The width and height of an image
 * img: raw image data
 */
typedef struct s_mlx_img
{
	int width;
	int height;
	void *img;
} t_mlx_img;

/* struct s_map
 * All information that can be obtained from about a map
 *
 * width, height: The width and height of a map
 * map: the actual map data (0: floor, 1: wall, 2: air/none),
 *      flattened row-major ordering
 * player_spawn_x/y: the x and y position of where the player spawns
 * player_facing: The direction the player is facing upon spawning,
 *                N: north, S: south, W: west, E: east
 */
typedef struct s_map
{
	int		width;
	int		height;
	char	*map;
	int		player_spawn_x;
	int		player_spawn_y;
	char	player_facing;
}	t_map;

/* struct s_texture_info
 * Information required for rendering the scene
 *
 * ceiling/floor_color: the color of the ceiling/floor
 *                      already formatted as RGB
 * tex_n/s/w/e: images for each of the wall faces

 */
typedef struct s_texture_info
{
	int	ceiling_color;
	int	floor_color;
	t_mlx_img tex_n;
	t_mlx_img tex_s;
	t_mlx_img tex_w;
	t_mlx_img tex_e;
}	t_tex_info;

// FUNCTIONS
t_map	*parse_map(t_tex_info *ti);

#endif
