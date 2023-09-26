/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:28:28 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/26 09:16:19 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	ft_abs_compare(char *s1, char *s2)
{
	int	i;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

bool	ft_is_line_space(char *str)
{
	if (!str)
		return (false);
	while (*str == ' ' || *str == '\n' || *str == '\f'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '\0')
		return (true);
	return (false);
}

bool	ft_reach_map(char *str)
{
	while (*str == ' ' || *str == '\f' || *str == '\r'
		|| *str == '\t' || *str == '\v')
		str++;
	if (*str != '1' && *str != '0')
		return (false);
	while (*str == '1' || *str == '0' || *str == ' ')
		str++;
	if (*str != '\n')
		return (false);
	return (true);
}

bool	ft_element_done(int *table)
{
	int	i;

	i = 0;
	while (i <= 5)
	{
		if (table[i] != 1)
			return (false);
		i++;
	}
	return (true);
}

char	*ft_first_last_line(char *line, int size)
{
	int	i;

	i = 0;
	while (i < (size - 1))
		line[i++] = '#';
	line[i] = '\0';
	return (line);
}
