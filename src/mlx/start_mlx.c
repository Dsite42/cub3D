/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:40:25 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/12 14:48:13 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	load_textures(t_data *data)
{
	data->mlx.north_img.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "./textures/Dsite42_800x800.cub.xpm",
			&data->mlx.north_img.width, &data->mlx.north_img.height);
	data->mlx.east_img.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "./textures/stonewall000.cub.xpm",
			&data->mlx.east_img.width, &data->mlx.east_img.height);
	data->mlx.south_img.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "./textures/arafa-spider.cub.xpm",
			&data->mlx.south_img.width, &data->mlx.south_img.height);
	data->mlx.west_img.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "./textures/brick_2.cub.xpm",
			&data->mlx.west_img.width, &data->mlx.west_img.height);
	if (data->mlx.north_img.mlx_img == NULL
		|| data->mlx.east_img.mlx_img == NULL
		|| data->mlx.south_img.mlx_img == NULL
		|| data->mlx.west_img.mlx_img == NULL)
	{
		perror("Error while loading the texture\n");
		window_close(data, MLX_ERROR);
		exit(0);
	}
}

static void	get_img_addr(t_data *data)
{
	data->mlx.win_img.addr = mlx_get_data_addr(data->mlx.win_img.mlx_img,
			&data->mlx.win_img.bpp, &data->mlx.win_img.line_len,
			&data->mlx.win_img.endian);
	data->mlx.north_img.addr = mlx_get_data_addr(data->mlx.north_img.mlx_img,
			&data->mlx.north_img.bpp, &data->mlx.north_img.line_len,
			&data->mlx.north_img.endian);
	data->mlx.east_img.addr = mlx_get_data_addr(data->mlx.east_img.mlx_img,
			&data->mlx.east_img.bpp, &data->mlx.east_img.line_len,
			&data->mlx.east_img.endian);
	data->mlx.south_img.addr = mlx_get_data_addr(data->mlx.south_img.mlx_img,
			&data->mlx.south_img.bpp, &data->mlx.south_img.line_len,
			&data->mlx.south_img.endian);
	data->mlx.west_img.addr = mlx_get_data_addr(data->mlx.west_img.mlx_img,
			&data->mlx.west_img.bpp, &data->mlx.west_img.line_len,
			&data->mlx.west_img.endian);
	if (data->mlx.win_img.addr == NULL || data->mlx.north_img.addr == NULL
		|| data->mlx.east_img.addr == NULL
		|| data->mlx.south_img.addr == NULL
		|| data->mlx.west_img.addr == NULL)
	{
		perror("Error while getting the address of the texture\n");
		window_close(data, MLX_ERROR);
	}
}

int	start_mlx(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	if (data->mlx.mlx_ptr == NULL)
	{
		perror("Error while initializing the mlx\n");
		window_close(data, MLX_ERROR);
	}
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr,
			data->mlx.win_img.width, data->mlx.win_img.height, "cub3D");
	data->mlx.win_img.mlx_img = mlx_new_image(data->mlx.mlx_ptr,
			data->mlx.win_img.width, data->mlx.win_img.height);
	if (data->mlx.win_ptr == NULL || data->mlx.win_img.mlx_img == NULL)
	{
		perror("Error while initializing the mlx\n");
		window_close(data, MLX_ERROR);
	}
	load_textures(data);
	get_img_addr(data);
	return (0);
}
