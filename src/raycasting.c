// index of coordinate = desired y * width + desired x - in indexed starting from 0
#include "cub3d.h"
#include <stdio.h>

void	set_starting_pdata(t_pos_v *pos, t_vars *vars)
{
	vars = *get_vars(); 
	pos->p_pos[0] = vars->map->player_spawn_x;
	pos->p_pos[1] = vars->map->player_spawn_y;
	if (vars->map->player_facing == 'N' ||	vars->map->player_facing == 'S')
	{
		pos->p_dir[1] = 1;
		if (vars->map->player_facing == 'N')
			pos->p_dir[1] = -1;
		pos->p_dir[0] = 0;
	}
	if (vars->map->player_facing == 'E' ||	vars->map->player_facing == 'W')
	{
		pos->p_dir[0] = 1;
		if (vars->map->player_facing == 'W')
			pos->p_dir[1] = -1;
		pos->p_dir[1] = 0;
	}
}

int	cast_rays(void)
{
	t_vars	*vars;
	t_pos_v	pl_v;
	t_vec	*screen;
	static int	i;


	vars = *get_vars();
	pl_v = vars->p_vec;
	if (!i){
		screen = get_screen_vector(pl_v);
		printf("initialized player data:\nposition vector = (%lf, %lf)\ndirection vector = (%lf, %lf)\nScreen = (%lf, %lf)\n",pl_v.p_pos[0], pl_v.p_pos[1], pl_v.p_dir[0], pl_v.p_dir[1], (*screen)[0], (*screen)[1]);
		i++;
		free(screen);
	}
	return (1);
}