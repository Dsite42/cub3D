/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:04:10 by ankinzin          #+#    #+#             */
/*   Updated: 2023/10/05 17:19:56 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/* This func checks the validity of each RGB color valure represented
** as a string, ensures each character in the RGB value is a digit and
** handles errors if an invalid character is encountered*/
static void	ft_check_rgb(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->rgb[i])
	{
		j = 0;
		while (data->rgb[i][j])
		{
			if ((j != 0) && data->rgb[i][j] == '\n')
			{
				j++;
				continue ;
			}
			if (!ft_isdigit(data->rgb[i][j]))
				ft_free_data_print_exit(data, "Error\n Invalid RGB input\n");
			j++;
		}
		i++;
	}
}

/* This func validates the RGB color value corresponding color
** components in a data sruct where F is Floorground and C
** is Ceiling*/
static bool	ft_validation_rbg_range(t_data *data)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(data->rgb[0]);
	g = ft_atoi(data->rgb[1]);
	b = ft_atoi(data->rgb[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (false);
	if (ft_abs_compare("F", data->generic[0]))
	{
		data->f_r = (unsigned char)r;
		data->f_g = (unsigned char)g;
		data->f_b = (unsigned char)b;
	}
	else if (ft_abs_compare("C", data->generic[0]))
	{
		data->c_r = (unsigned char)r;
		data->c_g = (unsigned char)g;
		data->c_b = (unsigned char)b;
	}
	return (true);
}

void	ft_validation_fc_rgb(t_data *data)
{
	int		i;

	data->rgb = ft_split(data->generic[1], ',');
	i = 0;
	while (data->rgb && data->rgb[i])
		i++;
	if (i != 3)
		ft_free_data_print_exit(data, "Error\nInvalid RBG input\n");
	ft_check_rgb(data);
	if (!(ft_validation_rbg_range(data)))
		ft_free_data_print_exit(data, "Error\nInvalid RBG range of input\n");
	ft_free_table(data->rgb);
	data->rgb = NULL;
}
