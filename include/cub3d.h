/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:07:04 by drobert-          #+#    #+#             */
/*   Updated: 2023/02/07 16:56:31 by leferrei         ###   ########.fr       */
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
	L_ARROW = 65361,
	R_ARROW = 65363,
	ESC = 65307
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
# define W_H 720

# define W_W 1280

# define MM_W (int)(W_W / 8)

# define MM_H (int)(W_W / 8)

# define MM_B_H (double)MM_H / 20

# define MM_B_W (double)MM_W / 20

# define MM_WALL_C 0x856548

# define MM_SPACER_SCALE 20

# define MM_SPACER ((double)MM_W  / ((double)MM_SPACER_SCALE / W_W * W_W))

# define MOUSE_AIM_STEPS (int)((int)W_W / 50)

# define VERY_BIG_N 1000000000000000019884624838656.00

# define FOV_DEG 80

# define DEG_TO_RAD (M_PI / 180.0)

# define FOV (FOV_DEG * DEG_TO_RAD)

# define MOUSE_SENS 1.5

# define CH_SIZE 1

# define CH_GAP 1

# define CH_TYPE 1 // 0 - Just color 1 - Outlined 2 - Cross shape

# define CH_COLOR 0xDD3333

# define CH_OCOLOR 0x000000

typedef double	t_vec[2];

typedef struct	s_ray_vs
{
	t_vec	ray_dir;
	t_vec	side_dist;
	t_vec	delta_dist;
	double	side_d_nd[2];
	double	wall_dist;
	int		steping[2]; //DDA algo steping angle, either 1 or -1 in x and y
	int		hit_;
	double	hit_pos;
	int		side; // 0 = top/bottom 1 = side
	int		face; //0 = S 1 = W 2 = N 3 = E
}	t_ray_vecs;

typedef	struct	s_pos_vect
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


// FUNCTIONS
t_map	*parse_map(char *file, t_tex_info *ti);
void	**get_mlx_ptr(void);
int		cast_rays(t_vars **vars);
int		set_starting_pdata(t_vars **vars);
void	draw_crosshair(t_mlx_img *img);
void	draw_minimap(t_mlx_img *img, t_vars	*vars);

//vector functions
void	add_vect(t_vec *sum_vect, t_vec vect_to_add);
void	scale_vect(t_vec *vect, double scale);
double	get_v_magnitude(t_vec vect);
void	rotate_vec(t_vec *vec, double angle);
int		compate_vectors(t_vec *vect1, t_vec *vect2);
void	set_vect_to_vect(t_vec *vect_to_set, t_vec *vect_to_get);
int		is_movement_coliding(t_vec *pos, t_vec *mov_vec, t_vars **vars);
void	normalize_vector(t_vec	*vec);
void	set_screen_vect(t_pos_v **pos);
double	get_angle_between_vec(t_vec	*vec1, t_vec *vec2);

// t_tex_info & t_map functions
void	init_tex_info(t_tex_info *t);
void	destroy_tex_info(t_tex_info *t);
int		convert_color(char **s, t_tex_info *ti);
int		convert_tex(char **s, t_tex_info *ti);
t_list	*set_texture_info(t_tex_info *ti, t_list *f);

// map functions
t_map	*get_map(t_list *l);
void	destroy_map(t_map *m);
int		get_map_fd(char *file);
t_list	*read_map(int fd);

// Utils
int		is_player_char(char c);
t_vars	**get_vars(void);
void	**get_mlx_ptr(void);
int		b_putstr_fd(char *str, int fd);
void    my_mlx_pixel_put(t_mlx_img *r_buf, int x, int y, int color);


// Debug
void	print_map(t_map *m);

#endif
