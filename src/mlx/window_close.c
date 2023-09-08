/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:37:13 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/08 10:15:44 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	window_close(t_data *data, int error_code)
{
	if (data->mlx.win_ptr != NULL)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	if (data->mlx.win_img.mlx_img != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.win_img.mlx_img);
	if (data->mlx.north_img.mlx_img != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.north_img.mlx_img);
	if (data->mlx.east_img.mlx_img != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.east_img.mlx_img);
	if (data->mlx.south_img.mlx_img != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.south_img.mlx_img);
	if (data->mlx.west_img.mlx_img != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.west_img.mlx_img);
	if (data->mlx.mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx.mlx_ptr);
		free(data->mlx.mlx_ptr);
	}
	if (error_code != 0)
		exit(error_code);
	exit (0);
}
