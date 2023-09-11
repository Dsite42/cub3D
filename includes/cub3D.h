/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:30:40 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/05 15:51:01 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include <float.h>
# include <errno.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

# define ROTRIGHT 65363
# define ROTLEFT 65361
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define TABSIZE 8

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

enum e_texEnum{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_data
{
	//mlx
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;

	//map
	int		map_colunms;
	int		map_rows;
	int		win_width;
	int		win_height;

	//raycaster
	int		win_half_width;
	int		win_half_height;
	double 	FOV;
	double 	half_FOV;
	double 	player_x;
	double 	player_y;
	double 	player_angle;
	double	ray_angle;
	double	ray_increment_angle;
	double	ray_precision;
	// ### Added Staff ###
	char			**rgb;
	char			**generic;
	char			**elements;
	char			**file_map;
	char			**map_cp;
	char			**map_flood;
	char			*line;
	void			*no_vptr;
	void			*so_vptr;
	void			*we_vptr;
	void			*ea_vptr;
	char			*file;
	int				file_size;
	int				bg_line;
	int				bg_column;
	int				p_spawn;
	int				p_posx;
	int				p_posy;
	int				map_start;
	int				magic[6];


}	t_data;

#endif
