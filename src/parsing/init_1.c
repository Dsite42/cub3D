/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:59:15 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/26 09:16:51 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_data_pointers(t_data *data)
{
	data->rgb = NULL;
	data->generic = NULL;
	data->elements = ft_split("NO SO WE EA F C", ' ');
	data->line = NULL;
	data->file_map = NULL;
	data->map_cp = NULL;
	data->map_flood = NULL;
	data->no_vptr = NULL;
	data->so_vptr = NULL;
	data->we_vptr = NULL;
	data->ea_vptr = NULL;
	data->no_path = NULL;
	data->we_path = NULL;
	data->so_path = NULL;
	data->ea_path = NULL;
}

void	init_data_structure(t_data *data, char *file)
{
	int		i;

	i = 0;
	init_data_pointers(data);
	while (i < 6)
		data->magic[i++] = 0;
	data->file = file;
	data->file_size = 0;
	data->bg_column = 0;
	data->bg_line = 0;
	data->p_spawn = 0;
	data->player_x = -1;
	data->player_y = -1;
}

void	init_dir_e_w(t_data *data)
{
	if (data->dir == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = data->fov;
	}
	else if (data->dir == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -data->fov;
	}
	else
		return ;
}

void	init_dir_n_s(t_data *data)
{
	if (data->dir == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = data->fov;
		data->plane_y = 0;
	}
	else if (data->dir == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -data->fov;
		data->plane_y = 0;
	}
	else
		return ;
}

void	init_dir(t_data *data)
{
	init_dir_n_s(data);
	init_dir_e_w(data);
}
