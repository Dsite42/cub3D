/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_ray_y_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:34:59 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/26 09:35:50 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

double	unit_ray_y_length(t_data *data)
{
	if (data->ray_angle == 0)
		return (0);
	return (1 / sin(deg_to_rad(data->ray_angle)));
}
