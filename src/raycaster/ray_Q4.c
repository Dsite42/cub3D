/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_Q4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:31:45 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/05 18:08:39 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double ray_Q4(t_data *data, int *i, int *j, int *wall)
{
	double	ray_x_length;
	double	ray_y_length;
	double	distance;
	double ray_x_dx_start = ceil(data->player_x) - data->player_x;
	double ray_x_sx_start = sqrt(pow(ray_x_dx_start, 2) + pow(tan(deg_to_rad(data->ray_angle)) * ray_x_dx_start, 2));
	double ray_y_dy_start = ceil(data->player_y) - data->player_y;
	double ray_y_sy_start = sqrt(pow(ray_y_dy_start, 2) + pow(ray_y_dy_start / tan(deg_to_rad(data->ray_angle)), 2));
	ray_x_length = 1.00001*ray_x_sx_start + *i * fabs(unit_ray_x_length(data));
	ray_y_length = 1.00001*ray_y_sy_start + *j * fabs(unit_ray_y_length(data));
	if (ray_x_length < ray_y_length)
	{
		data->ray_x = data->player_x + fabs(ray_x_length * cos(deg_to_rad(data->ray_angle)));
		data->ray_y = data->player_y + fabs(ray_x_length * sin(deg_to_rad(data->ray_angle)));
		*wall = map[(int)floor(data->ray_y)][(int)floor(data->ray_x)];
		data->sky_direction = EAST;
		distance = ray_x_length;
		*i = *i + 1;
	}
	else
	{
		data->ray_x = data->player_x + fabs(ray_y_length * cos(deg_to_rad(data->ray_angle)));
		data->ray_y = data->player_y + fabs(ray_y_length * sin(deg_to_rad(data->ray_angle)));
		*wall = map[(int)floor(data->ray_y)][(int)floor(data->ray_x)];
		data->sky_direction = SOUTH;
		distance = ray_y_length;
		*j = *j + 1;
	}
	return (distance);
}