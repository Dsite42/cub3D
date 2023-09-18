/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:42:17 by coder             #+#    #+#             */
/*   Updated: 2023/09/15 14:24:49 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This function ft_strlen is checking the length of a string.
// Return: length of a string as size_t.

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
