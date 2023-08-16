/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:47:18 by cgodecke          #+#    #+#             */
/*   Updated: 2023/08/16 19:10:06 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int old_old_color = RED_PIXEL;
int old_color = RED_PIXEL;

int map[10][10] = {
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

static char	sky_direction(t_data *data, double ray_x, double ray_y)
{
	int	row_before;
	int	col_before;
	double ray_precision = data->ray_precision;
	double tmp_ray_angle = data->ray_angle;
	double px;
	double py;

		//printf("ray_angle: %f\n", data->ray_angle);
	if ((int)data->ray_angle >= 0 && (int)data->ray_angle < 90)
	{
		px = (floor(ray_x + 1) - ray_x) / cos(deg_to_rad(data->ray_angle));
		py = (ray_y - floor(ray_y)) / sin(deg_to_rad(data->ray_angle));
		if (px < py)
			data->color = EAST;
		else
			data->color = NORTH;
	}
	else if ((int)data->ray_angle >= 90 && (int)data->ray_angle < 180)
	{
		px = (ray_x - floor(ray_x)) / cos(deg_to_rad(180 - data->ray_angle));
		py = (ray_y - floor(ray_y)) / sin(deg_to_rad(180 - data->ray_angle));
		if (px < py)
			data->color = WEST;
		else
			data->color = NORTH;
	}
	else if ((int)data->ray_angle >= 180 && (int)data->ray_angle < 270)
	{
		px = (ray_x - floor(ray_x)) / cos(deg_to_rad(data->ray_angle - 180));
		py = (floor(ray_y + 1) - ray_y) / sin(deg_to_rad(data->ray_angle - 180));
		if (px < py)
			data->color = WEST;
		else
			data->color = SOUTH;
	}
	else if ((int)data->ray_angle >= 270 && (int)data->ray_angle < 360)
	{
		px = (floor(ray_x + 1) - ray_x) / cos(deg_to_rad(360 - data->ray_angle));
		py = (floor(ray_y + 1) - ray_y) / sin(deg_to_rad(360 - data->ray_angle));
		if (px < py)
			data->color = EAST;
		else
			data->color = SOUTH;
	}

	else
		data->color = RED_PIXEL;
	//if (old_color != data->color)
	//	printf("ray_angle: %f, color: %d ray_x: %f, ray_y: %f\n", data->ray_angle, data->color, ray_x, ray_y);
	//old_color = data->color;
}

/*static char	sky_direction(t_data *data, double ray_x, double ray_y)
{
	int	row_before;
	int	col_before;
	double ray_precision = data->ray_precision;
	double tmp_ray_angle = data->ray_angle;

	row_before = floor(ray_y);
	col_before = floor(ray_x);
	//wall = map[(int)(floor(ray_y))][(int)(floor(ray_x))];
	if ((int)data->ray_angle%360 >= 90 && (int)data->ray_angle%360 < 270)
	{
		while (((int)(floor(ray_y - sin(deg_to_rad(tmp_ray_angle)) / ray_precision)) < (int)(floor(ray_y)))
		&& ((int)(floor(ray_x + cos(deg_to_rad(tmp_ray_angle)) / ray_precision)) < (int)(floor(ray_x))))
		{
			//printf("ray_precision: %f\n", ray_precision);
			//ray_precision += 100;
			tmp_ray_angle += data->ray_increment_angle;
		}

	}
	else
	{
		while (((int)(floor(ray_y - sin(deg_to_rad(tmp_ray_angle)) / ray_precision)) < (int)(floor(ray_y)))
		&& ((int)(floor(ray_x + cos(deg_to_rad(tmp_ray_angle)) / ray_precision)) > (int)(floor(ray_x))))
		{
			//printf("ray_precision: %f\n", ray_precision);
			//ray_precision += 100;
			tmp_ray_angle -= data->ray_increment_angle;
		}
	}

	if (((int)(floor(ray_y - sin(deg_to_rad(tmp_ray_angle)) / ray_precision)) < (int)(floor(ray_y))))
	//if (data->ray_angle > 0 && data->ray_angle < 180)
		data->color = 539923;
	//else if (data->ray_angle > 180 && data->ray_angle < 360)
	//{
	//	
	//}

	else
		data->color = BlUE_PIXEL;

}
*/

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
		if (old_old_color != RED_PIXEL && old_old_color == data->color && old_color != data->color)
			draw_line(data, ray_count - 1, 0, data->win_half_height - wall_height / 2, data->color);
		if (old_color == RED_PIXEL)
			old_color = data->color;
		else
		{
			old_old_color = old_color;
			old_color = data->color;
		}
		//printf("old_old_color: %d, old_color: %d, data->color: %d\n", old_old_color, old_color, data->color);
		// Calculate distance to wall
		double distance = sqrt(pow(data->player_x - ray_x, 2) + pow(data->player_y - ray_y, 2));
		distance *= cos(deg_to_rad(data->ray_angle - data->player_angle));
		wall_height = floor(data->win_height / distance);
		//Draw ray
		//printf("ray_count: %d, winn_half_height: %d, wall_height: %d\n", ray_count, data->win_half_height, wall_height);
		draw_line(data, ray_count, 0, data->win_half_height - wall_height / 2, data->color);
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
	render_background(data, &data->img, BLACK_PIXEL);
	render_rays(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}