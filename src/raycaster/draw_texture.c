/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:26:32 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/06 09:28:00 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	draw_north_south_texture(t_data *data, t_img *img, int y0, int y1)
{
	int		img_row;
	int		x;
	int		y;
	int		color;

	img_row = 0;
	if (y0 == 0)
		img_row = (data->wall_height - data->mlx.win_img.height) / 2;
	while (y0 < y1)
	{
		x = (int)((data->ray_x - floor(data->ray_x)) * img->width);
		y = (int)(img_row * img->height / data->wall_height);
		color = *(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8)));
		img_pix_put(&data->mlx.win_img, data->ray_count, y0, color);
		y0++;
		img_row++;
	}
}

static void	draw_east_west_texture(t_data *data, t_img *img, int y0, int y1)
{
	int		img_row;
	int		x;
	int		y;
	int		color;

	img_row = 0;
	if (y0 == 0)
		img_row = (data->wall_height - data->mlx.win_img.height) / 2;
	while (y0 < y1)
	{
		x = (int)((1 - (data->ray_y - floor(data->ray_y))) * img->width);
		y = (int)(img_row * img->height / data->wall_height);
		color = *(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8)));
		img_pix_put(&data->mlx.win_img, data->ray_count, y0, color);
		y0++;
		img_row++;
	}
}

void	draw_texture(t_data *data, int y0, int y1)
{
	t_img	img;

	if (data->sky_direction == NORTH)
		img = data->mlx.north_img;
	else if (data->sky_direction == EAST)
		img = data->mlx.east_img;
	else if (data->sky_direction == SOUTH)
		img = data->mlx.south_img;
	else if (data->sky_direction == WEST)
		img = data->mlx.west_img;
	if (data->sky_direction == NORTH || data->sky_direction == SOUTH)
		draw_north_south_texture(data, &img, y0, y1);
	else
		draw_east_west_texture(data, &img, y0, y1);
}
