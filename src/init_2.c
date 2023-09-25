/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:59:18 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/25 13:32:23 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	*get_addr_tex_img(t_data *img, t_teximg *dir_ptr)
{
	int			*tmp;
	int			x;
	int			y;

	tmp = (int *)malloc(sizeof(int) * img->tex_h * img->tex_w);
	if (!tmp)
		return (NULL);
	dir_ptr->addr = mlx_get_data_addr(dir_ptr->img, &(dir_ptr->bpp),
			&(dir_ptr->line_l), &(dir_ptr->endian));
	y = 0;
	while (y < img->tex_h)
	{
		x = 0;
		while (x < img->tex_w)
		{
			tmp[y * img->tex_w + x] = dir_ptr->addr[y * img->tex_w + x];
			x++;
		}
		y++;
	}
	return (tmp);
}

void	init_tex(t_data *img)
{
	img->tex = (int **)malloc(4 * sizeof(int *));
	if (!img->tex)
		exit (1);
	img->no_ptr.img = img->no_vptr;
	img->so_ptr.img = img->so_vptr;
	img->we_ptr.img = img->we_vptr;
	img->ea_ptr.img = img->ea_vptr;
}

/* fov(field of view) is the value which represents
the Field of Vision . For 1 is 90 degrees. */
void	init_data(t_data *data)
{
	data->w_img = 1920;
	data->h_img = 1080;
	data->addr = NULL;
	data->w_map = data->bg_line;
	data->h_map = data->bg_column;
	data->fov = 1;
	init_dir(data);
	data->pos_x = data->player_x;
	data->pos_y = data->player_y;
	data->tex_h = 64;
	data->tex_w = 64;
	init_tex(data);
	data->left = 0;
	data->right = 0;
	data->up = 0;
	data->down = 0;
	data->rotleft = 0;
	data->rotright = 0;
}
