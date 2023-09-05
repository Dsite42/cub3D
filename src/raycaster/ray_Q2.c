/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_Q2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:31:45 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/05 15:11:18 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double ray_Q2(t_data *data, int *i, int *j, int *wall)
{
	double	ray_x_length;
	double	ray_y_length;
	double	distance;
	int		wall_row;
	int		wall_column;

	double ray_x_dx_start = data->player_x - floor(data->player_x);
	double ray_x_sx_start = sqrt(pow(ray_x_dx_start, 2) + pow(tan(deg_to_rad(data->ray_angle)) * ray_x_dx_start, 2));
	double ray_y_dy_start = data->player_y - floor(data->player_y);
	double ray_y_sy_start = sqrt(pow(ray_y_dy_start, 2) + pow(ray_y_dy_start / tan(deg_to_rad(data->ray_angle)), 2));
	ray_x_length = 0.99999*ray_x_sx_start + *i * fabs(unit_ray_x_length(data));
	ray_y_length = 0.99999*ray_y_sy_start + *j * fabs(unit_ray_y_length(data));
	if (ray_x_length < ray_y_length)
	{
		wall_row = (int)(floor(data->player_y - fabs(ray_x_length * sin(deg_to_rad(data->ray_angle)))));
		wall_column = (int)(floor(data->player_x - fabs(ray_x_length * cos(deg_to_rad(data->ray_angle)))));
		*wall = map[wall_row][wall_column-1];
		//wall = map[(int)(floor(data->player_x - fabs(ray_x_length * cos(deg_to_rad(data->ray_angle)))) - 1)][(int)(floor(data->player_y + fabs(ray_x_length * sin(deg_to_rad(data->ray_angle)))))];
		data->sky_direction = WEST;
		distance = ray_x_length;
		*i = *i + 1;
	}
	else
	{
		wall_row = (int)(floor(data->player_y - fabs(ray_y_length * sin(deg_to_rad(data->ray_angle)))));
		wall_column = (int)(floor(data->player_x - fabs(ray_y_length * cos(deg_to_rad(data->ray_angle)))));
		*wall = map[wall_row-1][wall_column];
		//wall = map[(int)(floor(data->player_x - fabs(ray_y_length * cos(deg_to_rad(data->ray_angle)))))][(int)(floor(data->player_y + fabs(ray_y_length * sin(deg_to_rad(data->ray_angle)))))];
		data->sky_direction = NORTH;
		distance = ray_y_length;
		*j = *j + 1;
	}
	//printf("wall_row: %d, wall_column: %d\n", wall_row, wall_column);
	//printf("distance: %f ray_angle: %f ray_count: %d i: %d sky_direction: %d ray_x_length: %f ray_y_length: %f\n", distance, data->ray_angle, data->ray_count, i, data->sky_direction, ray_x_length, ray_y_length);
				
	if (*wall == 1)
		printf("Q3 wall_row: %d, wall_column: %d distance: %f ray_angle: %f sky_direction: %d\n", wall_row, wall_column, distance, data->ray_angle, data->sky_direction);
	return (distance);
}
