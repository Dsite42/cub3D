/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:04:06 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/15 14:15:18 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/* This func is handling the parse and validation of elements from a line of
** input, checking errors related ro the numbre of elements, invalid
** or repetition of elements*/
static void	ft_handle_element(t_data *data, char *line)
{
	int	i;

	i = 0;
	data->generic = ft_split(line, ' ');
	while (data->generic && data->generic[i])
		i++;
	if (i != 2)
		ft_free_data_print_exit(data, "Error\nSomething is wrong\n");
	i = 0;
	while (data->elements[i]
		&& !ft_abs_compare(data->generic[0], data->elements[i]))
		i++;
	if (data->elements[i] == NULL)
		ft_free_data_print_exit(data, "Error\nInvalid Element\n");
	if (data->magic[i] != 0)
		ft_free_data_print_exit(data, "Error\nRepeated Elements in Map\n");
	data->magic[i] = 1;
	ft_free_table(data->generic);
	data->generic = NULL;
}

/* Here we validate empty line we skip the, and we check for invalids too*/
void	ft_check_map_elements(t_data *data)
{
	int	i;

	i = 0;
	while (data->file_map[i])
	{
		if (ft_element_done(data->magic))
			return ;
		if (ft_is_line_space(data->file_map[i]))
		{
			i++;
			continue ;
		}
		if ((i == data->map_start) && !ft_element_done(data->magic))
			ft_free_data_print_exit(data, "Error\n Invalid Map Elements\n");
		ft_handle_element(data, data->file_map[i]);
		i++;
	}
}

/* Here we load images based on the confihurated values*/
static void	ft_check_init_elements(t_data *data)
{
	if (ft_abs_compare("NO", data->generic[0]))
		data->no_vptr = ft_load_image(data, data->generic[1]);
	else if (ft_abs_compare("SO", data->generic[0]))
		data->so_vptr = ft_load_image(data, data->generic[1]);
	else if (ft_abs_compare("WE", data->generic[0]))
		data->we_vptr = ft_load_image(data, data->generic[1]);
	else if (ft_abs_compare(data->generic[0], "F")
		|| ft_abs_compare(data->generic[0], "C"))
		ft_validation_fc_rgb(data);
}

void	ft_check_value_elements(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->file_map[i])
	{
		if (ft_element_done(data->magic))
			return ;
		if (ft_is_line_space(data->file_map[i]))
		{
			i++;
			continue ;
		}
		j = 0;
		data->generic = ft_split(data->file_map[i], ' ');
		while (data->elements[j]
			&& !ft_abs_compare(data->generic[0], data->elements[j]))
			j++;
		data->magic[j] = 1;
		ft_check_init_elements(data);
		ft_free_table(data->generic);
		data->generic = NULL;
		i++;
	}
}
