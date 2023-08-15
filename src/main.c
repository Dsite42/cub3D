/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:29:03 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/15 11:16:14 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	zero_struct_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img = (t_img){NULL, NULL, 0, 0, 0};
	data->cur_img = 0;

	//raycaster
	data->win_width = 640;
	data->win_height = 480;
	data->win_half_width = data->win_width / 2;
	data->win_half_height = data->win_height / 2;
	data->FOV = 60;
	data->half_FOV = data->FOV / 2;
	data->player_x = 3.50;
	data->player_y = 8.50;
	data->player_angle = 45;
	data->ray_angle = 0;
	data->ray_increment_angle = data->FOV / data->win_width;
	data->ray_precision = 128;
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
	mlx_loop_hook(data.mlx_ptr, &render_image, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify,
		StructureNotifyMask, &window_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
