/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:59:41 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/15 10:59:58 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_line(t_data *data, int raycount, int y0, int y1, int raycolor)
{
	while (y0 < y1)
	{
		img_pix_put(&data->img, raycount, y0, raycolor);
		y0++;
	}
}
