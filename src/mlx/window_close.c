/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:37:13 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/29 14:26:23 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	window_close(t_data *data)
{
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.win_img.mlx_img);
	mlx_destroy_display(data->mlx.mlx_ptr);
	free(data->mlx.mlx_ptr);
	exit (0);
}
