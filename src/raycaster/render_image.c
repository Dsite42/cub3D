/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:47:18 by cgodecke          #+#    #+#             */
/*   Updated: 2023/09/06 09:20:19 by cgodecke         ###   ########.fr       */
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
/*
int map[5][5] = {
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
};
*/

void	draw_north_south_texture(t_data *data, t_img *img, int y0, int y1)
{
	int		img_row;
	int		x;
	int		y;
	int		color;

	img_row = 0;
	if (y0 == 0)
		img_row = (data->wall_height - data->mlx.win_img.height) / 2;
	while (y0 < y1)
	{
		x = (int)((data->ray_x - floor(data->ray_x)) * img->width);
		y = (int)(img_row * img->height / data->wall_height);
		color = *(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8)));
		img_pix_put(&data->mlx.win_img, data->ray_count, y0, color);
		y0++;
		img_row++;
	}
}

void	draw_east_west_texture(t_data *data, t_img *img, int y0, int y1)
{
	int		img_row;
	int		x;
	int		y;
	int		color;

	img_row = 0;
	if (y0 == 0)
		img_row = (data->wall_height - data->mlx.win_img.height) / 2;
	while (y0 < y1)
	{
		x = (int)((1 - (data->ray_y - floor(data->ray_y))) * img->width);
		y = (int)(img_row * img->height / data->wall_height);
		color = *(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8)));
		img_pix_put(&data->mlx.win_img, data->ray_count, y0, color);
		y0++;
		img_row++;
	}
}

void	draw_texture(t_data *data, int y0, int y1)
{
	t_img	img;

	if (data->sky_direction == NORTH)
		img = data->mlx.north_img;
	else if (data->sky_direction == EAST)
		img = data->mlx.east_img;
	else if (data->sky_direction == SOUTH)
		img = data->mlx.south_img;
	else if (data->sky_direction == WEST)
		img = data->mlx.west_img;
	if (data->sky_direction == NORTH || data->sky_direction == SOUTH)
	{
		draw_north_south_texture(data, &img, y0, y1);
	}
	else
	{
		draw_east_west_texture(data, &img, y0, y1);
	}
}

static void	render_background(t_data *data, t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mlx.win_img.height)
	{
		j = 0;
		while (j < data->mlx.win_img.width)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

static void	render_rays(t_data *data)
{
	int		wall;
	double distance;
	int i;
	int j;

	data->ray_count = 0;
	data->ray_angle = (int)(data->player_angle + data->half_FOV) % 360;
	while (data->ray_count < data->mlx.win_img.width)
	{
 		// Wall finder
		i = 0;
		j = 0;
        wall = 0;
		data->ray_x = data->player_x;
		data->ray_y = data->player_y;

        while (wall == 0)
		{
			if (data->ray_angle >= 0 && data->ray_angle < 90)
			{
				distance = ray_q1(data, &i, &j, &wall);

			}
			else if (data->ray_angle >= 90 && data->ray_angle < 180)
			{
				distance = ray_q2(data, &i, &j, &wall);
			}
            else if (data->ray_angle >= 180 && data->ray_angle < 270)
            {
				distance = ray_q3(data, &i, &j, &wall);
			}
			else if (data->ray_angle >= 270 && data->ray_angle < 360)
			{
				distance = ray_q4(data, &i, &j, &wall);
			}

			else
			{
				printf("data->ray_angle: %f\n", data->ray_angle);
				break;
            //printf("dx: %f, dy: %d\n", ray_x + (((ray_y - floor_to_next_lower_box(ray_y)) / tan(deg_to_rad(data->ray_angle)))), floor_to_next_lower_box(ray_y));
			
			
			//ray_x += cos(deg_to_rad(data->ray_angle)) / data->ray_precision;
            //ray_y -= sin(deg_to_rad(data->ray_angle)) / data->ray_precision;
           // ray_x += cos(deg_to_rad(data->ray_angle));// / data->ray_precision;
			//printf("deg_to_rad(data->ray_angle): %f\n", sin(deg_to_rad(data->ray_angle)));
           // ray_y -= sin(deg_to_rad(data->ray_angle));// / data->ray_precision;
            //wall = map[(int)(floor(ray_y) / BOX_WIDTH)][(int)(floor(ray_x) / BOX_WIDTH)];
       		}
		}



///////
/*
{ 
			if (fmin(data->ray_x - floor(data->ray_x), ceil(data->ray_x) - data->ray_x) > 1 / data->ray_precision && fmin(data->ray_y - floor(data->ray_y), ceil(data->ray_y) - data->ray_y) > 1 / data->ray_precision)
			{
            	data->ray_x += cos(deg_to_rad(data->ray_angle)) / data->ray_precision;
            	data->ray_y -= sin(deg_to_rad(data->ray_angle)) / data->ray_precision;
			}
			else
			{
            	data->ray_x += cos(deg_to_rad(data->ray_angle)) / data->ray_precision_high;
            	data->ray_y -= sin(deg_to_rad(data->ray_angle)) / data->ray_precision_high;
			}
			//printf("deg_to_rad(data->ray_angle): %f\n", sin(deg_to_rad(data->ray_angle)));
            wall = map[(int)(floor(data->ray_y))][(int)(floor(data->ray_x))];
			if (wall == 0)
			{
				ray_x_before = data->ray_x;
				ray_y_before = data->ray_y;
				//printf("ray_x_box: %d, ray_y_box: %d\n", (int)(floor(ray_x)), (int)(floor(ray_y)));
				//printf("ray_x: %f, ray_y: %f, wall: %d ray_angle: %f ray_count: %d\n", ray_x, ray_y, wall, data->ray_angle, ray_count);
			}
 }
*/


///////




		


			//exit(0);






		
		//printf("X: %f y: %f angle: %f\n", data->ray_x, data->ray_y, data->ray_angle);
		//sky_direction(data, ray_x_before, ray_y_before);
		//check_sky_direction(data, data->ray_count, data->wall_height);
		//printf("old_old_color: %d, old_color: %d, data->color: %d\n", old_old_color, old_color, data->color);
		// Calculate distance to wall
		//distance = sqrt(pow(data->player_x - data->ray_x, 2) + pow(data->player_y - data->ray_y, 2));
		distance *= cos(deg_to_rad(data->ray_angle - data->player_angle));
		data->wall_height = floor(data->mlx.win_img.height / distance);
		//Draw ray
		//printf("ray_count: %d, winn_half_height: %d, wall_height: %d\n", ray_count, (data->mlx.win_height / 2), wall_height);
		draw_line(data, data->ray_count, 0, (data->mlx.win_img.height / 2) - data->wall_height / 2, data->sky_direction);
		//draw_line(data, data->ray_count, 0, (data->mlx.win_img.height / 2) - data->wall_height / 2, BLACK_PIXEL);
		draw_line(data, data->ray_count, (data->mlx.win_img.height / 2) + data->wall_height / 2, data->mlx.win_img.height, GREEN_PIXEL);
		//printf("ray_count: %d, winn_half_height: %d, wall_height: %d\n", data->ray_count, (data->mlx.win_img.height / 2), data->wall_height);
		
		if (data->wall_height < data->mlx.win_img.height)
			draw_texture(data, (data->mlx.win_img.height / 2) - data->wall_height / 2, (data->mlx.win_img.height / 2) + data->wall_height / 2);
		else
		{
			draw_texture(data, 0, data->mlx.win_img.height);
		}
		
		data->ray_angle = (data->ray_angle - data->ray_increment_angle);
		if (data->ray_angle < 0)
			data->ray_angle += 360;
		data->ray_count++;
		//if (data->ray_count == data->mlx.win_img.width)
		//	exit(0);	
	}
	
}

/*
void	texture_to_img(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		color;

	i = 0;
	while (i < data->mlx.win_height)
	{
		j = 0;
		while (j < data->mlx.win_width)
		{
			x = (int)(j * data->mlx.north_img_width / data->mlx.win_width);
			y = (int)(i * data->mlx.north_img_height / data->mlx.win_height);
			color = *(int *)(data->mlx.north_img.addr + (y
						* data->mlx.north_img.line_len + x
						* (data->mlx.north_img.bpp / 8)));
			img_pix_put(&data->mlx.win_img, j++, i, color);
		}
		++i;
	}
}
*/

int	render_image(t_data *data)
{
	if (data->mlx.win_ptr == NULL)
		return (1);
	//render_background(data, &data->mlx.win_img, BLACK_PIXEL);
	//texture_to_img(data);
	render_rays(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.win_img.mlx_img, 0, 0);
	return (0);
}