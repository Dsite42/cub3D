/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:29:03 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/29 16:22:51 by cgodecke         ###   ########.fr       */
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

	// map
	data->map_rows = 10;
	data->map_columns = 10;
	
	//raycaster
	data->mlx.win_img.width = 1280;
	data->mlx.win_img.height = 960;
	data->FOV = 60;
	data->half_FOV = data->FOV / 2;
	data->player_x = 7.60;
	data->player_y = 2.50;
	data->player_angle = 45;
	data->ray_angle = 0;
	data->ray_increment_angle = data->FOV / data->mlx.win_img.width;
	data->ray_precision = 512;
	data->sky_direction = RED_PIXEL;
	data->prev_sky_direction = RED_PIXEL;
	data->prev_prev_sky_direction = RED_PIXEL;

	// texture
	data->texture.width = 8;
	data->texture.height = 8;
	data->texture.color0 = 0x000000;
	data->texture.color1 = 0xFFFFFF;
}
int	main(int argc, char **argv)
{
	t_data	data;
	t_texture texture;

	argv = NULL;

	if (argc != 2)
	{
		perror("Error: wrong number of arguments\n");
		return (0);
	}
	zero_struct_data(&data);
	start_mlx(&data);
	//exit(0);
	mlx_loop_hook(data.mlx.mlx_ptr, &render_image, &data);
	mlx_hook(data.mlx.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.mlx.win_ptr, DestroyNotify,
		StructureNotifyMask, &window_close, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
