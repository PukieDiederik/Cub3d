#include "cub3d.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "mlx.h"

t_list *read_map(int fd)
{
	t_list *tmp;
	t_list *ret;
	char* line;

	ret = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!line[0] || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			ft_lstclear(&tmp, free);
			return (0);
		}
		ft_lstadd_back(&ret, tmp);
		line = get_next_line(fd);
	}
	return ret;
}

// will open a file descriptor or return -1 on error;
int get_map_fd(char *file)
{
	size_t len;

	len= ft_strlen(file);
	if (len < 4 || file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
	{
		ft_putstr_fd("Error: Invalid map name\n", 2);
		return (-1);
	}
	return (open(file, O_RDONLY));
}

void	clear_split(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		++i;
	}
	free(s);
}

//loads an image by path
t_mlx_img *load_img(char *path, t_mlx_img *img)
{
	img->img = mlx_xpm_file_to_image(*get_mlx_ptr(), path,
		 	&img->width, &img->height);
	return (img);
}

//Will convert string to an image or color
int convert_tex(char **s, t_tex_info *ti, int *is_init)
{
	t_mlx_img *img;
	char *ss;

	if (!ft_strncmp(s[0], "NO", 3))
	{
		*is_init |= 1 << 5;
		img = &ti->tex_n;
	}
	else if (!ft_strncmp(s[0], "SO", 3))
	{
		*is_init |= 1 << 4;
		img = &ti->tex_s;
	}
	else if (!ft_strncmp(s[0], "WE", 3))
	{
		*is_init |= 1 << 3;
		img = &ti->tex_w;
	}
	else if (!ft_strncmp(s[0], "EA", 3))
	{
		*is_init |= 1 << 2;
		img = &ti->tex_e;
	}
	else
		return (0);
	ss = ft_substr(s[1], 0, ft_strlen(s[1]) - 1);
	load_img(ss, img);
	free(ss);
	if (!img->img)
	{
		ft_putstr_fd("Error: Could not find image\n", 2);
		return (0);
	}
	return (1);
}

// Will return the start of the map on success
// Will return NULL if there was an issue
// is_initialized will be 00111111b if everything is initialized
t_list	*set_texture_info(t_tex_info *ti, t_list *f)
{
	int is_initialized = 3;
	int i = 0;
	char **s_str;

	while (i < 6 && f)
	{
		s_str = ft_split((char *)f->content, ' ');
		if (!s_str || !s_str[0] || !s_str[1] || s_str[2])
		{
			ft_putstr_fd("Error: while parsing texture info", 2);
			clear_split(s_str);
			return (0);
		}
		printf("%s %s", s_str[0], s_str[1]);
		if (s_str[1][1])
			convert_tex(s_str, ti, &is_initialized);
		++i;
		clear_split(s_str);
		f = f->next;
	}
	if (is_initialized != 0b00111111)
		ft_putstr_fd("Error: Not every part of the texture info is initialized", 2);
	return (f);
};

// This function will return a t_map (allocated) object with the correct with, height and map
t_map *parse_map(char *file, t_tex_info *ti)
{
	int fd;
	t_list *l;

	fd = get_map_fd(file);
	if (fd < 0)
		return (0);
	l = read_map(fd);
	printf("%s\n", (char *)l->content);
	printf("%d\n", ft_lstsize(l));
	ti->ceiling_color = 0;
	set_texture_info(ti, l);
	ft_lstclear(&l, free);
	close(fd);
	return (0);
}