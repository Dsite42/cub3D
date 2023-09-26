/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:45:15 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/26 18:12:04 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_wall(t_data *data, double step_factor, double player_angle)
{
	double	x;
	double	y;

	x = data->player_x + cos(deg_to_rad(player_angle)) * step_factor;
	y = data->player_y - sin(deg_to_rad(player_angle)) * step_factor;
	return (data->map_flood[(int)(floor(y))][(int)(floor(x))] - 48);
}

static void	go_step(t_data *data, double step_factor, double player_angle)
{
	if (is_wall(data, step_factor, player_angle) == 0 || is_wall(data, step_factor, player_angle) == 40)
	{
		data->player_x += cos(deg_to_rad(player_angle)) * step_factor;
		data->player_y -= sin(deg_to_rad(player_angle)) * step_factor;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	double	step_factor;

	step_factor = 0.15;
	if (keysym == XK_Escape)
		window_close(data, 0);
	else if (keysym == XK_Left)
		data->player_angle = ((int)(data->player_angle + 5) % 360);
	else if (keysym == XK_Right)
	{
		data->player_angle = ((int)(data->player_angle - 5) % 360);
		if (data->player_angle < 0)
			data->player_angle += 360;
	}
	else if (keysym == XK_w)
		go_step(data, step_factor, data->player_angle);
	else if (keysym == XK_s)
		go_step(data, step_factor, (int)(data->player_angle + 180) % 360);
	else if (keysym == XK_a)
		go_step(data, step_factor, (int)(data->player_angle + 90) % 360);
	else if (keysym == XK_d)
		go_step(data, step_factor, (int)(data->player_angle - 90) % 360);

	return (0);
}
