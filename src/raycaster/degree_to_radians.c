/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degree_to_radians.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:04:14 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/15 11:05:52 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double	degree_to_radians(double degree)
{
	double	pi;

	pi = 3.14159265359;
	pi = M_PI;
	return (degree * pi / 180);
}
