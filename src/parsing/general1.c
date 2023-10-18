/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:28:30 by ankinzin          #+#    #+#             */
/*   Updated: 2023/10/18 16:21:17 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_real_size(char *str)
{
	int		size;
	bool	r_wall;

	size = 0;
	if (!str)
		return (size);
	r_wall = false;
	while (*str != '\0' && *str != '\n')
	{
		if ((*str == '1' || *str == '0') && !r_wall)
			r_wall = true;
		if (*str == '\t' && !r_wall)
			size += TABSIZE;
		else
			size++;
		str++;
	}
	return (size);
}
