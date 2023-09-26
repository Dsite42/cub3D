/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_q2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:31:45 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/26 14:01:10 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static double	ray_x_dx_start(t_data *data)
{
	return (data->player_x - floor(data->player_x));
}

static double	ray_y_dy_start(t_data *data)
{
	return (data->player_y - floor(data->player_y));
}

static double	appy_shorter_x_ray(t_data *data, double ray_x_length,
		int *i, int *wall)
{
	data->ray_x = data->player_x
		- fabs(ray_x_length * cos(deg_to_rad(data->ray_angle)));
	data->ray_y = data->player_y
		- fabs(ray_x_length * sin(deg_to_rad(data->ray_angle)));
	*wall = data->map_flood[(int)floor(data->ray_y)][(int)floor(data->ray_x) - 1] - 48;
	data->sky_direction = WEST;
	*i = *i + 1;
	return (ray_x_length);
}

static double	appy_shorter_y_ray(t_data *data, double ray_y_length,
		int *j, int *wall)
{
	data->ray_x = data->player_x
		- fabs(ray_y_length * cos(deg_to_rad(data->ray_angle)));
	data->ray_y = data->player_y
		- fabs(ray_y_length * sin(deg_to_rad(data->ray_angle)));
	*wall = data->map_flood[(int)floor(data->ray_y) - 1][(int)floor(data->ray_x)] - 48;
	data->sky_direction = NORTH;
	*j = *j + 1;
	return (ray_y_length);
}

double	ray_q2(t_data *data, int *i, int *j, int *wall)
{
	double	ray_x_length;
	double	ray_y_length;
	double	distance;
	double	ray_x_sx_start;
	double	ray_y_sy_start;

	ray_x_sx_start = sqrt(pow(ray_x_dx_start(data), 2)
			+ pow(tan(deg_to_rad(data->ray_angle)) * ray_x_dx_start(data), 2));
	ray_y_sy_start = sqrt(pow(ray_y_dy_start(data), 2)
			+ pow(ray_y_dy_start(data) / tan(deg_to_rad(data->ray_angle)), 2));
	ray_x_length = 0.9999999 * ray_x_sx_start + *i
		* fabs(unit_ray_x_length(data));
	ray_y_length = 0.9999999 * ray_y_sy_start + *j
		* fabs(unit_ray_y_length(data));
	if (ray_x_length < ray_y_length)
		distance = appy_shorter_x_ray(data, ray_x_length, i, wall);
	else
		distance = appy_shorter_y_ray(data, ray_y_length, j, wall);
	return (distance);
}
