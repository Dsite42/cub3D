/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:40:25 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/28 15:40:11 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	start_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_height, "cub3D");
	data->main_img.mlx_img = mlx_new_image(data->mlx_ptr,
			data->win_width, data->win_height);
	data->north_img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, "/Users/cgodecke/Desktop/Core/cub3D/textures/brick_2.xpm",
			&data->north_img_width, &data->north_img_height);
	if (data->north_img.mlx_img == NULL)
	{
		perror("Error while loading the texture\n");
		exit(0);
	}
	data->main_img.addr = mlx_get_data_addr(data->main_img.mlx_img, &data->main_img.bpp,
			&data->main_img.line_len, &data->main_img.endian);
	data->north_img.addr = mlx_get_data_addr(data->north_img.mlx_img, &data->north_img.bpp,
			&data->north_img.line_len, &data->north_img.endian);
	//if (data->mlx_ptr == NULL || data->win_ptr == NULL
	//	|| data->img.mlx_img == NULL || data->img.addr == NULL)
	//{
	//	if (data->mlx_ptr != NULL)
	//		free(data->mlx_ptr);
	//	if (data->win_ptr != NULL)
	//		free(data->win_ptr);
	//	if (data->img.mlx_img != NULL)
	//		free(data->img.mlx_img);
	//	if (data->img.addr != NULL)
	//		free(data->img.addr);
	//	perror("Error while initializing the mlx\n");
	//	exit (MLX_ERROR);
	//}
	return (0);
}
