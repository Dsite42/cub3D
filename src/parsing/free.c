/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:58:42 by ankinzin          #+#    #+#             */
/*   Updated: 2023/10/18 15:53:53 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free (table[i]);
		i++;
	}
	free (table);
}

static void	ft_free_data_print_exit_1(t_data *data)
{
	if (data->rgb)
		ft_free_table(data->rgb);
	if (data->generic)
		ft_free_table(data->generic);
	if (data->elements)
		ft_free_table(data->elements);
	if (data->file_map)
		ft_free_table(data->file_map);
	if (data->map_cp)
		ft_free_table(data->map_cp);
	if (data->map_flood)
		ft_free_table(data->map_flood);
}

void	ft_free_data_print_exit(t_data *data, char *msg)
{
	msg = NULL;
	if (data->no_path)
		free(data->no_path);
	if (data->so_path)
		free(data->so_path);
	if (data->we_path)
		free(data->we_path);
	if (data->ea_path)
		free(data->ea_path);
	ft_free_data_print_exit_1(data);
	if (data->line)
		free (data->line);
	exit (1);
}

void	ft_free_data(t_data *data)
{
	if (data->line)
		free (data->line);
	if (data->rgb)
		ft_free_table(data->rgb);
	if (data->generic)
		ft_free_table(data->generic);
	if (data->elements)
		ft_free_table(data->elements);
	if (data->file_map)
		ft_free_table(data->file_map);
	if (data->map_cp)
		ft_free_table(data->map_cp);
	if (data->map_flood)
		ft_free_table(data->map_flood);
}
