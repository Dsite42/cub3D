/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:04:16 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/26 13:41:00 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/* This func reads lines from a file descritor, duplicates each line, and stores
** the dup lines in a 2D array of strings*/
static void	ft_file_to_dup_ptr(t_data *data, int fd)
{
	int	i;

	i = 0;
	data->file_map = (char **)malloc(sizeof(char *) * (data->file_size + 1));
	while (data->line)
	{
		data->file_map[i++] = ft_strdup(data->line);
		free (data->line);
		data->line = get_next_line(fd);
	}
	data->file_map[i] = NULL;
	close (fd);
}

/* This func performs file handling tasks such as opening, checking
** and reopening a file for reading, we also check for map size
** file existence...*/
void	ft_check_fd(t_data *data)
{
	int	fd;

	fd = open(data->file, O_RDONLY);
	if (fd < 0)
	{
		close (fd);
		ft_free_data_print_exit(data, "Error\nInvalid fd! File doesn't exit\n");
	}
	data->line = get_next_line(fd);
	ft_check_map_size(data, fd);
	if (data->bg_line < 3 || data->bg_column < 3)
		ft_free_data_print_exit(data, "Error\nInvalid map size\n");
	close (fd);
	fd = open(data->file, O_RDONLY);
	data->line = get_next_line(fd);
	ft_file_to_dup_ptr(data, fd);
}

void	ft_check_map_extension(t_data *data, const char *extension)
{
	int	i;
	int	len_file;
	int	len_ext;

	len_file = ((int)ft_strlen(data->file));
	len_ext = ((int)ft_strlen(extension));
	i = -1;
	if (len_file < 5)
		ft_free_data_print_exit(data, "Error\nInvalid map name\n");
	while (++i < 4)
		if (data->file[--len_file] != extension[--len_ext])
			ft_free_data_print_exit(data, "Error: Invalid map extension\n");
}

/* This goes through the mnap and searches for the line numbere where
** map data begins, and identify it as the start of the map*/
void	ft_map_start_line(t_data *data)
{
	int	i;

	i = 0;
	while (data->file_map[i])
	{
		if (ft_reach_map(data->file_map[i]))
		{
			data->map_start = i;
			return ;
		}
		i++;
	}
}

void	ft_validation(t_data *data)
{
	int	i;

	ft_check_map_extension(data, ".cub");
	ft_check_fd(data);
	ft_map_start_line(data);
	ft_check_map_elements(data);
	i = 0;
	while (i < 6)
		data->magic[i++] = 0;
	ft_check_value_elements(data);
	ft_handle_map_cp(data);
	ft_check_map_tiles(data);
	ft_copy_table(data);
	ft_print_map(data->map_cp);
	ft_flood_fill(data, data->player_x, data->player_y, "NSEW0");
}
