/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:04:13 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/13 15:37:39 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/* This func reads lines from a file descriptor and determines the size of
** a map represented by those lines, counts number of rows and collumns in
** the map while skipping any lines that arent part of the map*/
void	ft_check_map_size(t_data *data, int fd)
{
	int	line_size;

	while (data->line)
	{
		data->file_size++;
		if (ft_reach_map(data->line))
		{
			while (data->line)
			{
				data->file_size++;
				data->bg_column += 1;
				line_size = ft_real_size(data->line);
				if (line_size > data->bg_line)
					data->bg_line = line_size;
				free (data->line);
				data->line = get_next_line(fd);
			}
		}
		if (data->line)
		{
			free (data->line);
			data->line = get_next_line(fd);
		}
	}
}

/* This func is used to validate the map elements and handles player spawn
** points by checking for duplicates and storing player's position and
** direction*/
static void	ft_check_map_tile_1(t_data *data, char tile, int line, int column)
{
	if (!ft_strchr("10NSEW#", tile))
		ft_free_data_print_exit(data, "Error\nInvalid map tile\n");
	if (ft_strchr("NSEW", tile))
	{
		if (data->p_spawn >= 1)
			ft_free_data_print_exit(data, "Error\nMultiples player spawn\n");
		data->p_spawn = 1;
		data->player_y = line;
		data->player_x = column;
		data->dir = tile;
	}
}

/* This checks if we have a player in the map*/
void	ft_check_map_tiles(t_data *data)
{
	int		i;
	int		j;

	j = 0;
	while (data->map_cp[j])
	{
		i = 0;
		while (data->map_cp[j][i])
		{
			ft_check_map_tile_1(data, data->map_cp[j][i], j, i);
			i++;
		}
		j++;
	}
	if (data->p_spawn == 0)
		ft_free_data_print_exit(data,
			"Error\nThe map doesn't have a player spawn\n");
}

/* this is used to create a duplicate of the 2D array of strings and
** stores it in another array, useful to preserve the original map
** while making modifications to the copied version*/
void	ft_copy_table(t_data *data)
{
	int		i;

	i = 0;
	data->map_flood = (char **)malloc(sizeof(char *) * (data->bg_column + 3));
	while (data->map_cp[i])
	{
		data->map_flood[i] = ft_strdup(data->map_cp[i]);
		i++;
	}
	data->map_flood[i] = NULL;
}

/* here we perform flood fill recursively to connect the cells with X by
** checking the boundary walls and validating the current cells characters
** within the specified elements*/
void	ft_flood_fill(t_data *data, int x, int y, char *elements)
{
	if (x < 0 || x >= (data->bg_line + 2) || y < 0 || y >= (data->bg_column + 2))
		return ;
	if (data->map_flood[y][x] == '#')
		ft_free_data_print_exit(data,
			"Error\nThe map isn't surrounded by walls\n");
	if (!ft_strchr(elements, data->map_flood[y][x]))
		return ;
	data->map_flood[y][x] = 'X';
	ft_flood_fill(data, (x + 1), y, elements);
	ft_flood_fill(data, (x - 1), y, elements);
	ft_flood_fill(data, x, (y + 1), elements);
	ft_flood_fill(data, x, (y - 1), elements);
}
