/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:29:03 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/08 09:30:38 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	zero_struct_data(t_data *data)
{
	// mlx
	data->mlx.mlx_ptr = NULL;
	data->mlx.win_ptr = NULL;
	data->mlx.win_img = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	data->mlx.north_img = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	data->mlx.east_img = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	data->mlx.south_img = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	data->mlx.west_img = (t_img){NULL, NULL, 0, 0, 0, 0, 0};

	// map
	data->map_rows = 10;
	data->map_columns = 10;
	
	//raycaster
	data->mlx.win_img.width = 1280;
	data->mlx.win_img.height = 960;
	data->FOV = 60;
	data->half_FOV = data->FOV / 2;
	data->player_x = 2.4;
	data->player_y = 2.7;
	data->player_angle = 45;
	data->ray_angle = 0;
	data->ray_increment_angle = data->FOV / data->mlx.win_img.width;
	data->sky_direction = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	argv = NULL;

	if (argc != 2)
	{
		perror("Error: wrong number of arguments\n");
		return (0);
	}
	zero_struct_data(&data);
	start_mlx(&data);
	mlx_loop_hook(data.mlx.mlx_ptr, &render_image, &data);
	mlx_hook(data.mlx.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.mlx.win_ptr, DestroyNotify,
		StructureNotifyMask, &window_close, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
