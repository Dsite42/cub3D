/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:45:15 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/17 13:37:51 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int map2[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1},
};


static int	is_wall(t_data *data, double step_factor, int button)
{
	double	x;
	double	y;

	if (button == 'w')
	{
		x = data->player_x + cos(deg_to_rad(data->player_angle)) * step_factor;
		y = data->player_y - sin(deg_to_rad(data->player_angle)) * step_factor;
		return (map2[(int)(floor(y))][(int)(floor(x))]);
	}
	if (button == 's')
	{
		x = data->player_x - cos(deg_to_rad(data->player_angle)) * step_factor;
		y = data->player_y + sin(deg_to_rad(data->player_angle)) * step_factor;
		return (map2[(int)(floor(y))][(int)(floor(x))]);
	}
	return (1);
}

static void	press_w(t_data *data, double step_factor)
{
	if (is_wall(data, step_factor, 'w') == 0)
	{
		data->player_x += cos(deg_to_rad(data->player_angle)) * step_factor;
		data->player_y -= sin(deg_to_rad(data->player_angle)) * step_factor;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	double	step_factor;

	step_factor = 0.25;
	if (keysym == XK_Escape)
		window_close(data);
	else if (keysym == XK_a)
	{
		data->player_angle = ((int)(data->player_angle + 5) % 360);
		printf("data->player_angle: %f\n", data->player_angle);
	}
	else if (keysym == XK_d)
	{
		data->player_angle = ((int)(data->player_angle - 5) % 360);
		if (data->player_angle < 0)
			data->player_angle += 360;
		//printf("data->player_angle: %f\n", data->player_angle);
	}
	else if (keysym == XK_w)
	{
		press_w(data, step_factor);
		//printf("data->player_x: %f data->player_y: %f\n", data->player_x, data->player_y);
	}
	else if (keysym == XK_s)
	{
		if (is_wall(data, step_factor, 's') == 0)
		{
			data->player_x -= cos(deg_to_rad(data->player_angle)) * step_factor;
			data->player_y += sin(deg_to_rad(data->player_angle)) * step_factor;
		}
	}
	return (0);
}


/*	else if (keysym == XK_w)
	{
		if (data->player_x + cos(deg_to_rad(data->player_angle))
			* step_factor > 1 && data->player_x + cos(deg_to_rad(data->player_angle))
			* step_factor < data->map_columns - 1
		&& data->player_y -sin(deg_to_rad(data->player_angle)) * step_factor < data->map_rows - 1 && data->player_y - sin(deg_to_rad(data->player_angle)) * step_factor > 1)
		{
			data->player_x += cos(deg_to_rad(data->player_angle)) * step_factor;
			data->player_y -= sin(deg_to_rad(data->player_angle)) * step_factor;
		}
		printf("data->player_x: %f data->player_y: %f\n", data->player_x, data->player_y);
	}
	else if (keysym == XK_s)
	{
		if (data->player_x - cos(deg_to_rad(data->player_angle)) * step_factor > 1 && data->player_x - cos(deg_to_rad(data->player_angle)) * step_factor < data->map_columns - 1
		&& data->player_y + sin(deg_to_rad(data->player_angle)) * step_factor < data->map_rows - 1 && data->player_y + sin(deg_to_rad(data->player_angle)) * step_factor > 1)
		{
			data->player_x -= cos(deg_to_rad(data->player_angle)) * step_factor;
			data->player_y += sin(deg_to_rad(data->player_angle)) * step_factor;
		}
	}
*/






/*	else if (keysym == XK_w)
	{
		if ((data->player_x + (cos(deg_to_rad(data->player_angle)) * step_factor) < data->map_columns-1)
		&& (data->player_y - sin(deg_to_rad(data->player_angle)) * step_factor < data->map_rows-1))
		{
			data->player_x += cos(deg_to_rad(data->player_angle)) * step_factor;
			data->player_y -= sin(deg_to_rad(data->player_angle)) * step_factor;
		}
		printf("data->player_x: %f data->player_y: %f\n", data->player_x, data->player_y);
	}
	else if (keysym == XK_s)
	{
		if ((data->player_x - cos(deg_to_rad(data->player_angle)) * step_factor < data->map_columns - 1)
		&& (data->player_y + sin(deg_to_rad(data->player_angle)) * step_factor < data->map_rows - 1))
		{
			data->player_x -= cos(deg_to_rad(data->player_angle)) * step_factor;
			data->player_y += sin(deg_to_rad(data->player_angle)) * step_factor;
		}
	}
*/