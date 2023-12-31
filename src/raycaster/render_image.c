/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:47:18 by cgodecke          #+#    #+#             */
/*   Updated: 2023/10/18 16:18:20 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static double	find_wall_distance(t_data *data, int *i, int *j, int *wall)
{
	double	distance;

	while (*wall == 0 || *wall == 'X' - 48)
	{
		if (data->ray_angle >= 0 && data->ray_angle < 90)
			distance = ray_q1(data, i, j, wall);
		else if (data->ray_angle >= 90 && data->ray_angle < 180)
			distance = ray_q2(data, i, j, wall);
		else if (data->ray_angle >= 180 && data->ray_angle < 270)
			distance = ray_q3(data, i, j, wall);
		else if (data->ray_angle >= 270 && data->ray_angle < 360)
			distance = ray_q4(data, i, j, wall);
	}
	return (distance);
}

static void	draw(t_data *data)
{
	draw_line(data, 0, (data->mlx.win_img.height / 2)
		- data->wall_height / 2, data->ceiling_color);
	draw_line(data, (data->mlx.win_img.height / 2) + data->wall_height
		/ 2, data->mlx.win_img.height, data->floor_color);
	if (data->wall_height < data->mlx.win_img.height)
		draw_texture(data, (data->mlx.win_img.height / 2)
			- data->wall_height / 2, (data->mlx.win_img.height / 2)
			+ data->wall_height / 2);
	else
		draw_texture(data, 0, data->mlx.win_img.height);
}

static void	render_rays(t_data *data)
{
	int		wall;
	double	distance;
	int		i;
	int		j;

	data->ray_count = 0;
	data->ray_angle = (int)(data->player_angle + data->half_fov) % 360;
	while (data->ray_count < data->mlx.win_img.width)
	{
		i = 0;
		j = 0;
		wall = 0;
		data->ray_x = data->player_x;
		data->ray_y = data->player_y;
		distance = find_wall_distance(data, &i, &j, &wall)
			* cos(deg_to_rad(data->ray_angle - data->player_angle));
		data->wall_height = floor(data->mlx.win_img.height / distance);
		draw(data);
		data->ray_angle = (data->ray_angle - data->ray_increment_angle);
		if (data->ray_angle < 0)
			data->ray_angle += 360;
		data->ray_count++;
	}
}

int	render_image(t_data *data)
{
	if (data->mlx.win_ptr == NULL)
		return (1);
	render_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.win_img.mlx_img, 0, 0);
	return (0);
}
