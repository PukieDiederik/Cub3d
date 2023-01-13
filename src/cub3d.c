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
	(void)map;

	if (argc != 2)
	{
		write(2, "Wrong amount of args\n", ft_strlen("Wrong amount of args\n"));
		return (1);
	}
	*get_mlx_ptr() = mlx_init();
	map = parse_map(argv[1], &tex_info);
	print_map(map);
	printf("Welcome to cub3d!\n");
	destroy_map(map);
	free(map);
	destroy_tex_info(&tex_info);
}