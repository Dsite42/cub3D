/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:30:40 by cgodecke          #+#    #+#             */
/*   Updated: 2023/10/18 16:29:05 by cgodecke         ###   ########.fr       */
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
# include <errno.h>
# include <stdint.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

# define TABSIZE 8
# define MLX_ERROR 30
# define CEILING_COLOR 0x0000FF
# define FLOOR_COLOR 3110932

// parsing
typedef struct s_iso_res {
	float	x;
	float	y;
	float	z;
}		t_iso_res;

typedef struct s_color {
	float	c0;
	float	c1;
	float	step;
}		t_color;

enum e_texEnum{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_copy
{
	int		*i;
	int		*j;
	bool	r_wall;
	char	*src;
	char	*dst;
}		t_copy;

// Raycaster
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

// mlx
typedef struct s_mlx
{
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
	int				map_columns;
	int				map_rows;
	t_mlx			mlx;
	double			fov;
	double			half_fov;
	double			player_x;
	double			player_y;
	double			player_angle;
	double			ray_angle;
	double			ray_increment_angle;
	double			ray_x;
	double			ray_y;
	int				ray_count;
	int				wall_height;
	int				sky_direction;

	char			*no_path;
	char			*ea_path;
	char			*so_path;
	char			*we_path;
	char			dir;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
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
	float			pos_x;
	float			pos_y;
	int				file_size;
	int				bg_line;
	int				bg_column;
	int				p_spawn;
	int				p_posx;
	int				p_posy;
	int				map_start;
	int				magic[6];
	unsigned char	f_r;
	unsigned char	f_g;
	unsigned char	f_b;
	unsigned char	c_r;
	unsigned char	c_g;
	unsigned char	c_b;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
}	t_data;

// --> general.c
bool	ft_abs_compare(char *s1, char *s2);
bool	ft_is_line_space(char *str);
bool	ft_reach_map(char *str);
bool	ft_element_done(int *table);
char	*ft_first_last_line(char *line, int size);

// --> general_1.c
int		ft_real_size(char *str);

// --> init_1.c
void	init_data_pointers(t_data *data);
void	init_data_structure(t_data *data, char *file);
void	init_dir_e_w(t_data *data);
void	init_dir_n_s(t_data *data);
void	init_dir(t_data *data);

// --> init_2.c
void	init_data(t_data	*data);

// --> validation.c
void	ft_check_fd(t_data *data);
void	ft_check_map_extension(t_data *data, const char *extension);
void	ft_map_start_line(t_data *data);
void	ft_validation(t_data *data);

// --> validation_element.c
void	ft_check_map_elements(t_data *data);
void	ft_check_value_elements(t_data *data);

//--> validation_image.c
void	*ft_load_image(t_data *data, char *file);
void	ft_validation_fc_rgb(t_data *data);

// --> validation_map.c
void	ft_check_map_size(t_data *data, int fd);
void	ft_check_map_tiles(t_data *data);
void	ft_copy_table(t_data *data);
void	ft_flood_fill(t_data *data, int x, int y, char *elements);

// --> free.c
void	ft_free_table(char **table);
void	ft_free_data_print_exit(t_data *data, char *msg);
void	ft_free_data(t_data *data);
void	ft_free_tex(t_data *data);

// --> map_file.c
void	ft_handle_map_cp(t_data *data);

//Raycaster
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
void	interface(t_data *data);

#endif
