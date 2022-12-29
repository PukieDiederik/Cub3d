#include "mlx.h"
#include "cub3d.h"
#include "libft.h"
#include <stdio.h>

void **get_mlx_ptr(void)
{
	static void *mlx = 0;
	return (&mlx);
}

int main(int argc, char **argv)
{
	t_map		*map;
	t_tex_info	tex_info;

	if (argc != 2)
	{
		write(2, "Wrong amount of args\n", ft_strlen("Wrong amount of args\n"));
		return (1);
	}
	*get_mlx_ptr() = mlx_init();
	map = parse_map(argv[1], &tex_info);
	printf("%p\n", map);
	printf("Welcome to cub3d!");
	mlx_destroy_image(*get_mlx_ptr(), tex_info.tex_n.img);
	mlx_destroy_image(*get_mlx_ptr(), tex_info.tex_s.img);
	mlx_destroy_image(*get_mlx_ptr(), tex_info.tex_w.img);
	mlx_destroy_image(*get_mlx_ptr(), tex_info.tex_e.img);
}