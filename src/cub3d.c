#include <stdio.h>
#include "cub3d.h"

int main()
{
	t_map		*map;
	t_tex_info	tex_info;

	map = parse_map(&tex_info);
	printf("%p\n", map);
	printf("Welcome to cub3d!");
}