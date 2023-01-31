/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:07:04 by drobert-          #+#    #+#             */
/*   Updated: 2023/01/31 16:53:56 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlx.h>
# include <math.h>

enum {
	ON_KEYDOWN = 2,
	ON_DESTROY = 17,
	WIN_HEIGHT = 720,
	WIN_WIDTH = 1280
};

// STRUCTURES
/* struct s_mlx_img
 * All information required to work with an mlx image
 *
 * width, height: The width and height of an image
 * img: raw image data
 */
typedef struct s_mlx_img
{
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_img;

# define FOV_DEG 90

# define DEG_TO_RAD (M_PI / 180.0)

# define FOV (FOV_DEG * DEG_TO_RAD)

typedef double t_vec[2];

typedef	struct	s_pos_vect
{
	t_vec	p_pos;
	t_vec	p_dir;
}	t_pos_v;

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
 * is_initialized: Integer with each bit representing
 *                 which variables have been initialized
 * ceiling/floor_color: the color of the ceiling/floor
 *                      already formatted as RGB
 * tex_n/s/w/e: images for each of the wall faces

 */
typedef struct s_texture_info
{
	int			is_initialized;
	int			ceiling_color;
	int			floor_color;
	t_mlx_img	tex_n;
	t_mlx_img	tex_s;
	t_mlx_img	tex_w;
	t_mlx_img	tex_e;
}	t_tex_info;


typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_mlx_img	render_buffer;
	t_tex_info	tex_info;
	t_map		*map;
	t_pos_v		p_vec;
}	t_vars;


// FUNCTIONS
t_map	*parse_map(char *file, t_tex_info *ti);
void	**get_mlx_ptr(void);
int		cast_rays(void);
void	set_starting_pdata(t_pos_v *pos, t_vars *vars);
t_vec	*get_screen_vector(t_pos_v pos);
// t_tex_info & t_map functions
void	init_tex_info(t_tex_info *t);
void	destroy_tex_info(t_tex_info *t);

int		convert_color(char **s, t_tex_info *ti);
int		convert_tex(char **s, t_tex_info *ti);
t_list	*set_texture_info(t_tex_info *ti, t_list *f);

t_map	*get_map(t_list *l);
void	destroy_map(t_map *m);
int		get_map_fd(char *file);
t_list	*read_map(int fd);

// Utils
int		is_player_char(char c);
t_vars	**get_vars(void);
void	**get_mlx_ptr(void);
int		b_putstr_fd(char *str, int fd);


// Debug
void	print_map(t_map *m);

#endif
