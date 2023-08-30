/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:02:51 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/30 10:52:39 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_sky_direction(t_data *data, int ray_count, int wall_height)
{
	if (data->prev_prev_sky_direction != RED_PIXEL
		&& data->prev_prev_sky_direction == data->sky_direction
		&& data->prev_sky_direction != data->sky_direction)
	{
		//draw_line(data, ray_count - 1, 0, (data->mlx.win_img.height / 2)
		//	- wall_height / 2, data->sky_direction);
		int i = 0;
		while(i < data->mlx.win_img.height)
		{
			//printf("i: %d\n", i);
			int color = *(int *)(data->mlx.win_img.addr + (i * data->mlx.win_img.line_len + (ray_count - 0) * (data->mlx.win_img.bpp / 8)));
			img_pix_put(&data->mlx.win_img, ray_count -1, i, color);
			i++;

		}
		printf("ray_count: %d X: %f y: %f angle: %f\n", ray_count, data->ray_x, data->ray_y, data->ray_angle);
		data->prev_sky_direction = data->sky_direction;
	}
	if (data->prev_sky_direction == RED_PIXEL)
		data->prev_sky_direction = data->sky_direction;
	else
	{
		data->prev_prev_sky_direction = data->prev_sky_direction;
		data->prev_sky_direction = data->sky_direction;
	}
}

static void	sky_q1(t_data *data, double ray_x, double ray_y)
{
	double	px;
	double	py;

	px = (floor(ray_x + 1) - ray_x) / cos(deg_to_rad(data->ray_angle));
	py = (ray_y - floor(ray_y)) / sin(deg_to_rad(data->ray_angle));
	if (px < py)
		data->sky_direction = EAST;
	else
		data->sky_direction = NORTH;
}

static void	sky_q2(t_data *data, double ray_x, double ray_y)
{
	double	px;
	double	py;

	px = (ray_x - floor(ray_x)) / cos(deg_to_rad(180 - data->ray_angle));
	py = (ray_y - floor(ray_y)) / sin(deg_to_rad(180 - data->ray_angle));
	if (px < py)
		data->sky_direction = WEST;
	else
		data->sky_direction = NORTH;
}

static void	sky_q3(t_data *data, double ray_x, double ray_y)
{
	double	px;
	double	py;

	px = (ray_x - floor(ray_x)) / cos(deg_to_rad(data->ray_angle - 180));
	py = (floor(ray_y + 1) - ray_y)
		/ sin(deg_to_rad(data->ray_angle - 180));
	if (px < py)
		data->sky_direction = WEST;
	else
		data->sky_direction = SOUTH;
}

void	sky_direction(t_data *data, double ray_x, double ray_y)
{
	double	px;
	double	py;

	if ((int)data->ray_angle >= 0 && (int)data->ray_angle < 90)
		sky_q1(data, ray_x, ray_y);
	else if ((int)data->ray_angle >= 90 && (int)data->ray_angle < 180)
		sky_q2(data, ray_x, ray_y);
	else if ((int)data->ray_angle >= 180 && (int)data->ray_angle < 270)
		sky_q3(data, ray_x, ray_y);
	else if ((int)data->ray_angle >= 270 && (int)data->ray_angle < 360)
	{
		px = (floor(ray_x + 1) - ray_x)
			/ cos(deg_to_rad(360 - data->ray_angle));
		py = (floor(ray_y + 1) - ray_y)
			/ sin(deg_to_rad(360 - data->ray_angle));
		if (px < py)
			data->sky_direction = EAST;
		else
			data->sky_direction = SOUTH;
	}
}
