/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leferrei <leferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:21:37 by leferrei          #+#    #+#             */
/*   Updated: 2023/02/09 16:44:25 by leferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

enum {
	OUTLINED = 1,
	CROSS = 2,
	SIMPLE = 0
};

//Window options
# define W_H 720
# define W_W 1280

//Minimap options
# define MM_SCALE 7
# define MM_WALL_C 0x856548
# define MM_SPACER_SCALE 20

//FOV options
# define FOV_DEG 80

//Mouse options
# define MOUSE_SENS 1.5

//Crosshair options
# define CH_SIZE 1
# define CH_GAP 1
# define CH_TYPE OUTLINED
# define CH_COLOR 0xDD3333
# define CH_OCOLOR 0x000000

#endif