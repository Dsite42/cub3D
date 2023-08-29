/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:47:18 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/29 13:31:36 by cgodecke         ###   ########.fr       */
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

void draw_texture(t_data *data, int ray_count, int y0, int y1, t_img img, double ray_x_before, double ray_y_before, int wall_height)
{
	int		img_row;
	int		x;
	int		y;
	int		color;

	img_row = 0;
	if (data->sky_direction == NORTH || data->sky_direction == SOUTH)
	{
		while (y0 < y1)
		{
			x = (int)((ray_x_before - floor(ray_x_before))
					* data->north_img_width);
			y = (int)(img_row * data->north_img_height / wall_height);
			color = *(int *)(data->north_img.addr + (y
						* data->north_img.line_len + x 
						* (data->north_img.bpp / 8)));
			img_pix_put(&data->main_img, ray_count, y0, color);
			y0++;
			img_row++;
		}
	}
	else
	{
		while (y0 < y1)
		{
			x = (int)((ray_y_before - floor(ray_y_before))
					* data->north_img_width);
			y = (int)(img_row * data->north_img_height / wall_height);
			color = *(int *)(data->north_img.addr + (y
						* data->north_img.line_len + x
						* (data->north_img.bpp / 8)));
			img_pix_put(&data->main_img, ray_count, y0, color);
			y0++;
			img_row++;
		}
	}
}

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
		printf("ray_count: %d, winn_half_height: %d, wall_height: %d\n", ray_count, data->win_half_height, wall_height);
		if (wall_height < data->win_height)
			draw_texture(data, ray_count, data->win_half_height - wall_height / 2, data->win_half_height + wall_height / 2, data->north_img, ray_x_before, ray_y_before, wall_height);
		data->ray_angle = (data->ray_angle - data->ray_increment_angle);
		if (data->ray_angle < 0)
			data->ray_angle += 360;
		ray_count++;
		//if (ray_count == data->win_width)
		//	exit(0);	
	}
	
}

void	texture_to_img(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		color;

	i = 0;
	while (i < data->win_height)
	{
		j = 0;
		while (j < data->win_width)
		{
			x = (int)(j * data->north_img_width / data->win_width);
			y = (int)(i * data->north_img_height / data->win_height);
			color = *(int *)(data->north_img.addr + (y * data->north_img.line_len + x * (data->north_img.bpp / 8)));
			img_pix_put(&data->main_img, j++, i, color);
		}
		++i;
	}
}


int	render_image(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(data, &data->main_img, BLACK_PIXEL);
	//texture_to_img(data);
	render_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->main_img.mlx_img, 0, 0);
	return (0);
}