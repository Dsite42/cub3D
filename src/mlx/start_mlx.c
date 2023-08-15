/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:40:25 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/15 10:41:27 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	start_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_height, "cub3D");
	data->img.mlx_img = mlx_new_image(data->mlx_ptr,
			data->win_width, data->win_height);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (data->mlx_ptr == NULL || data->win_ptr == NULL
		|| data->img.mlx_img == NULL || data->img.addr == NULL)
	{
		if (data->mlx_ptr != NULL)
			free(data->mlx_ptr);
		if (data->win_ptr != NULL)
			free(data->win_ptr);
		if (data->img.mlx_img != NULL)
			free(data->img.mlx_img);
		if (data->img.addr != NULL)
			free(data->img.addr);
		perror("Error while initializing the mlx\n");
		exit (MLX_ERROR);
	}
	return (0);
}
