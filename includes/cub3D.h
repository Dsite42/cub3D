/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:30:40 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/18 17:53:48 by ankinzin         ###   ########.fr       */
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
# include "../src/minilibx-linux/mlx.h"

# define ROTRIGHT 65363
# define ROTLEFT 65361
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define TABSIZE 8

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

typedef struct s_teximg {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_l;
	int		endian;
}	t_teximg;

typedef struct s_data
{
	//mlx
	void	*mlx_ptr;
	void	*win_ptr;
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
	int				w_img;
	int				h_img;
	char			*addr;
	int				bpp;
	int				line_l;
	int				endian;
	int				w_map;
	int				h_map;
	char			dir;
	//float			fov;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	int				tex_w;
	int				tex_h;
	int				**tex;
	t_teximg		no_ptr;
	t_teximg		so_ptr;
	t_teximg		we_ptr;
	t_teximg		ea_ptr;
	int				left;
	int				right;
	int				up;
	int				down;
	int				rotleft;
	int				rotright;
	void			*mlx;
	void			*mlx_win;
	void			*img;
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
	float			fov;
	float			pos_x;
	float			pos_y;
	//int				t_teximg;
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
}	t_data;

typedef struct s_copy
{
	int		*i;
	int		*j;
	bool	r_wall;
	char	*src;
	char	*dst;
}		t_copy;

// --> general.c
bool		ft_abs_compare(char *s1, char *s2);
bool		ft_is_line_space(char *str);
bool		ft_reach_map(char *str);
bool		ft_element_done(int *table);
char		*ft_first_last_line(char *line, int size);

// --> general_2.c
int			ft_real_size(char *str);
void	ft_print_map(char **map);

// --> init_1.c
void		init_data_pointers(t_data *data);
void		init_data_structure(t_data *data, char *file);
void		init_dir_e_w(t_data *data);
void		init_dir_n_s(t_data *data);
void		init_dir(t_data *data);

// --> init_2.c
void		init_data(t_data	*data);
//void		init_tex(t_data *img);
int			*get_addr_tex_img(t_data *img, t_teximg *dir_ptr);

// --> validation.c
void		ft_check_fd(t_data *data);
void		ft_check_map_extension(t_data *data, const char *extension);
void		ft_map_start_line(t_data *data);
void		ft_validation(t_data *data);

// --> validation_element.c
void		ft_check_map_elements(t_data *data);
void		ft_check_value_elements(t_data *data);

//--> validation_image.c
void		*ft_load_image(t_data *data, char *file);
void		ft_validation_fc_rgb(t_data *data);

// --> validation_map.c
void		ft_check_map_size(t_data *data, int fd);
void		ft_check_map_tiles(t_data *data);
void		ft_copy_table(t_data *data);
void		ft_flood_fill(t_data *data, int x, int y, char *elements);

// --> free.c
void		ft_free_table(char **table);
void		ft_free_data_print_exit(t_data *data, char *msg);
void		ft_free_data(t_data *data);
void		ft_free_tex(t_data *data);

// --> map_file.c
void		ft_handle_map_cp(t_data *data);
#endif
