#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

// Initializes tex_info with empty values
void init_tex_info(t_tex_info* t)
{
	t->is_initialized = 0;
	t->ceiling_color = 0;
	t->floor_color = 0;
	t->tex_n.img = 0;
	t->tex_s.img = 0;
	t->tex_e.img = 0;
	t->tex_w.img = 0;
}

void destroy_tex_info(t_tex_info* t)
{
	if ((t->is_initialized >> 5) & 1 && t->tex_n.img)
		mlx_destroy_image(*get_mlx_ptr(), t->tex_n.img);
	if ((t->is_initialized >> 4) & 1 && t->tex_s.img)
		mlx_destroy_image(*get_mlx_ptr(), t->tex_s.img);
	if ((t->is_initialized >> 3) & 1 && t->tex_e.img)
		mlx_destroy_image(*get_mlx_ptr(), t->tex_e.img);
	if ((t->is_initialized >> 2) & 1 && t->tex_w.img)
		mlx_destroy_image(*get_mlx_ptr(), t->tex_w.img);
	t->tex_n.img = 0;
	t->tex_s.img = 0;
	t->tex_e.img = 0;
	t->tex_w.img = 0;
	t->is_initialized = 0;
}
