/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:30:40 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/08 09:41:41 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>
# include <errno.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

# define MLX_ERROR 30
# define CEILING_COLOR 0x0000FF
# define FLOOR_COLOR 3110932

# define SOUTH 16764424
# define EAST 581375
# define NORTH 3148994
# define WEST 15437613

extern int map[10][20];

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_mlx
{
	//mlx
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	win_img;
	t_img	north_img;
	int		north_img_width;
    int		north_img_height;
	t_img	east_img;
	int		east_img_width;
	int		east_img_height;
	t_img	south_img;
	int		south_img_width;
	int		south_img_height;
	t_img	west_img;
	int		west_img_width;
	int		west_img_height;
}	t_mlx;

typedef struct s_data
{
	t_mlx	mlx;
	//map
	int		map_columns;
	int		map_rows;


	//raycaster
	double 	FOV;
	double 	half_FOV;
	double 	player_x;
	double 	player_y;
	double 	player_angle;
	double	ray_angle;
	double	ray_increment_angle;
	double	ray_x;
	double	ray_y;
	int		ray_count;
	int		wall_height;
	int		sky_direction;
}	t_data;

// mlx
int		window_close(t_data *data, int error_code);
int		start_mlx(t_data *data);
int		handle_keypress(int keysym, t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);

// raycaster
int		render_image(t_data *data);
void	draw_line(t_data *data, int y0, int y1, int raycolor);
double	deg_to_rad(double degree);
void	sky_direction(t_data *data, double ray_x, double ray_y);
void	check_sky_direction(t_data *data, int ray_count, int wall_height);
double	ray_q1(t_data *data, int *i, int *j, int *wall);
double	ray_q2(t_data *data, int *i, int *j, int *wall);
double	ray_q3(t_data *data, int *i, int *j, int *wall);
double	ray_q4(t_data *data, int *i, int *j, int *wall);
double	unit_ray_x_length(t_data *data);
double	unit_ray_y_length(t_data *data);
void	draw_texture(t_data *data, int y0, int y1);

#endif
