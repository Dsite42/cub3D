/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:47:18 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/28 14:00:19 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int map[10][20] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1},
};

int	bitmap [8][8] = {
                {1,1,1,1,1,1,1,1},
                {0,0,0,1,0,0,0,1},
                {1,1,1,1,1,1,1,1},
                {0,1,0,0,0,1,0,0},
                {1,1,1,1,1,1,1,1},
                {0,0,0,1,0,0,0,1},
                {1,1,1,1,1,1,1,1},
                {0,1,0,0,0,1,0,0}
            };

static void	render_background(t_data *data, t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->win_height)
	{
		j = 0;
		while (j < data->win_width)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

static void	render_rays(t_data *data)
{
	int		ray_count;
	double ray_x_before;
	double ray_y_before;
	int wall_height;

	ray_count = 0;
	data->ray_angle = (int)(data->player_angle + data->half_FOV) % 360;
	while (ray_count < data->win_width)
	{
 		// Wall finder
        int wall = 0;
		double ray_x = data->player_x;
		double ray_y = data->player_y;

        while (wall == 0)
		{
            ray_x += cos(deg_to_rad(data->ray_angle)) / data->ray_precision;
            ray_y -= sin(deg_to_rad(data->ray_angle)) / data->ray_precision;
			//printf("deg_to_rad(data->ray_angle): %f\n", sin(deg_to_rad(data->ray_angle)));
            wall = map[(int)(floor(ray_y))][(int)(floor(ray_x))];
			if (wall == 0)
			{
				ray_x_before = ray_x;
				ray_y_before = ray_y;
				//printf("ray_x_box: %d, ray_y_box: %d\n", (int)(floor(ray_x)), (int)(floor(ray_y)));
				//printf("ray_x: %f, ray_y: %f, wall: %d ray_angle: %f ray_count: %d\n", ray_x, ray_y, wall, data->ray_angle, ray_count);
			}
        }
		sky_direction(data, ray_x_before, ray_y_before);
		check_sky_direction(data, ray_count, wall_height);
		//printf("old_old_color: %d, old_color: %d, data->color: %d\n", old_old_color, old_color, data->color);
		// Calculate distance to wall
		double distance = sqrt(pow(data->player_x - ray_x, 2) + pow(data->player_y - ray_y, 2));
		distance *= cos(deg_to_rad(data->ray_angle - data->player_angle));
		wall_height = floor(data->win_height / distance);
		//Draw ray
		//printf("ray_count: %d, winn_half_height: %d, wall_height: %d\n", ray_count, data->win_half_height, wall_height);
		draw_line(data, ray_count, 0, data->win_half_height - wall_height / 2, data->sky_direction);
		draw_line(data, ray_count, data->win_half_height + wall_height / 2, data->win_height, GREEN_PIXEL);
		data->ray_angle = (data->ray_angle - data->ray_increment_angle);
		if (data->ray_angle < 0)
			data->ray_angle += 360;
		ray_count++;
		//if (ray_count == data->win_width)
		//	exit(0);	
	}
}

int	render_image(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	//render_background(data, &data->img, BLACK_PIXEL);
	//render_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}