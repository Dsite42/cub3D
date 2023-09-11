/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:28:30 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/11 10:41:29 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void ft_print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			write(STDOUT_FILENO, &map[i][j++], 1);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	write (STDOUT_FILENO, "\n", 1);
}
