/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:29:03 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/19 16:59:28 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	zero_struct_data(t_data *data)
{
	//data->mlx_ptr = NULL;
	//data->win_ptr = NULL;
	//data->img = (t_img){NULL, NULL, 0, 0, 0};
	//data->cur_img = 0;

	//raycaster
	data->win_width = 1920;
	data->win_height = 1080;
	data->win_half_width = data->win_width / 2;
	data->win_half_height = data->win_height / 2;
	data->FOV = 60;
	data->half_FOV = data->FOV / 2;
	data->player_x = 3.50;
	data->player_y = 8.50;
	data->player_angle = 45;
	data->ray_angle = 0;
	data->ray_increment_angle = data->FOV / data->win_width;
	data->ray_precision = 128;
}

int	main(int argc, char **argv)
{
	t_data	data;

	//argv = NULL;

	if (argc != 2)
	{
		perror("Error: wrong number of arguments\n");
		return (0);
	}
	data.file = argv[1];
	init_data_structure(&data, argv[1]);
	zero_struct_data(&data);
	ft_validation(&data);
	//init_data(&data);
	printf("Floor: R%i G%i B%i \n", data.f_r, data.f_g, data.f_b);
	printf("Ceiling: R%i G%i B%i\n", data.c_r, data.c_g, data.c_b);
	printf("NO_path:%s\n", data.NO_path);
	printf("EA_path:%s\n", data.EA_path);
	printf("SO_path:%s\n", data.SO_path);
	printf("WE_path:%s\n", data.WE_path);


	ft_putstr_fd("\n\n>>> VALIDATION OK! <<<\n", 1);
	ft_free_data_print_exit(&data, "Freed alles\n");
	return (0);
}
