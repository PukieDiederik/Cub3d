/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:07:04 by drobert-          #+#    #+#             */
/*   Updated: 2023/02/09 15:48:12 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlx.h>
# include <math.h>
# include "vector.h"
# include "options.h"

enum {
	ON_KEYDOWN = 2,
	ON_DESTROY = 17,
	L_ARROW = 65361,
	R_ARROW = 65363,
	ESC = 65307,
	W_K = 119,
	D_K = 97,
	S_K = 115,
	A_K = 100
};

enum
{
	SOUTH = 0,
	WEST = 1,
	NORTH = 2,
	EAST = 3
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

//Constants
# define VERY_BIG_N 1000000000000000019884624838656.00

typedef struct s_ray_vs
{
	t_vec	ray_dir;
	t_vec	side_dist;
	t_vec	delta_dist;
	double	side_d_nd[2];
	double	wall_dist;
	int		steping[2];
	int		hit_;
	double	hit_pos;
	int		side;
	int		face;
}	t_ray_vecs;

typedef struct s_pos_vect
{
	t_vec		p_pos;
	int			map_pos[2];
	t_vec		p_dir;
	t_ray_vecs	ray;
	t_vec		screen;
	double		camera_x;
	int			line_height;
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
	t_mlx_img	textures[4];
}	t_tex_info;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_mlx_img	render_buffer;
	t_tex_info	tex_info;
	t_map		*map;
	t_pos_v		*p_vec;
}	t_vars;

// Raycasting functions
void			**get_mlx_ptr(void);
int				cast_rays(t_vars **vars);
int				set_starting_pdata(t_vars **vars);
void			draw_crosshair(t_mlx_img *img);
void			draw_minimap(t_mlx_img *img, t_vars	*vars);
void			set_screen_vect(t_pos_v **pos);
void			set_starting_rdata(t_vars **vars);
int				set_starting_pdata(t_vars **vars);
void			set_initial_x_rayd(t_vars **vars, int x_coord);

//Constant functions
double			mm_spacer(void);
double			mm_b_s(void);
double			fov(void);
int				mm_s(void);
double			d_to_r(void);

// t_tex_info & t_map functions
void			init_tex_info(t_tex_info *t);
void			destroy_tex_info(t_tex_info *t);
int				convert_color(char **s, t_tex_info *ti);
int				convert_tex(char **s, t_tex_info *ti);
t_list			*set_texture_info(t_tex_info *ti, t_list *f);

// map functions
t_map			*parse_map(char *file, t_tex_info *ti);
t_map			*get_map(t_list *l);
void			destroy_map(t_map *m);
int				get_map_fd(char *file);
t_list			*read_map(int fd);

//Interaction functions
int				kb_interaction(int keycode, t_vars **vars);
int				mouse_aim(int x, int y, t_vars **vars);
int				is_movement_coliding(t_vec *pos, t_vec *mov_vec, t_vars **vars);

// Utils
int				is_player_char(char c);
t_vars			**get_vars(void);
void			**get_mlx_ptr(void);
int				b_putstr_fd(char *str, int fd);
int				clear_exit(void);
int				are_options_valid(void);

// View
unsigned int	*get_img_color(t_mlx_img *img, int x, int y);
void			my_mlx_pixel_put(t_mlx_img *r_buf, int x, int y, int color);
void			draw_line(t_vars *vars, int x, double hit_x);
// Debug
void			print_map(t_map *m);

#endif
