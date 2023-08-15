/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:45:15 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/15 10:45:41 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		window_close(data);
	else if (keysym == XK_a)
		data->player_angle += 5;
	else if (keysym == XK_d)
		data->player_angle -= 5;
	else if (keysym == XK_w)
	{
		data->player_x += cos(degree_to_radians(data->player_angle)) * 0.5;
		data->player_y -= sin(degree_to_radians(data->player_angle)) * 0.5;
	}
	else if (keysym == XK_s)
	{
		data->player_x -= cos(degree_to_radians(data->player_angle)) * 0.5;
		data->player_y += sin(degree_to_radians(data->player_angle)) * 0.5;
	}
	return (0);
}
