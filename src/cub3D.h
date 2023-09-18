/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:30:40 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/15 14:19:24 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "includes/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>
# include <errno.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

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

}	t_data;

#endif
