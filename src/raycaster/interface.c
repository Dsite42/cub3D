/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:24:03 by cgodecke          #+#    #+#             */
/*   Updated: 2023/10/04 11:29:16 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static double	get_player_angle(t_data *data)
{
	if (data->dir == 'N')
		return (90);
	else if (data->dir == 'E')
		return (0);
	else if (data->dir == 'S')
		return (270);
	else
		return (180);
}

static int	color_encoding(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	interface(t_data *data)
{
	data->player_x += 0.5;
	data->player_y += 0.5;
	data->player_angle = get_player_angle(data);
	data->floor_color = color_encoding(data->f_r, data->f_g, data->f_b);
	data->ceiling_color = color_encoding(data->c_r, data->c_g, data->c_b);

ft_print_map(data->map_flood);
printf("wall:%c\n", (char)(data->map_flood[5][8]) - 0);
//int i = 0;
//while(map[i] != NULL)
//{
//	printf("map_test:%s\n", data->map_flood[i]);
//	i++;
//}
}
