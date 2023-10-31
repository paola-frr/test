/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:47:24 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/31 02:48:03 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_background(t_data *data)
{
	int i;
	int j;
	int	color;

	i = -1;
	color = d->f_r >> 16 | d->f_g >> 8 | d->f_b;
	while (++i < height / 2)
	{
		j = 0;
		while (j < width)
		{
			d->img[(i + height / 2) * width + (j + 0)] = color;
			j++;
		}
	}
	i = -1;
	color = d->c_r >> 16 | d->c_g >> 8 | d->c_b;
	while (i < height / 2)
	{
		j = 0;
		while (j < width)
		{
			d->img[(i + 0) * width + (j + 0)] = color;
			j++;
		}
	}
}

static void	draw_wall(t_data *data, t_ray *ray, int i)
{
	int	offsetX;
	int	offsetY;
	int	texture_color;
	int	distance_from_top;
	int	index;

	index = choice_of_texture(ray);
	if (ray->was_hit_vertical == 1)
		offsetX = (int)(ray->wall_hit_y * g_texture[index].width / g_tile_size) % g_texture[index].width;
	else
		offsetX = (int)(ray->wall_hit_x * g_texture[index].width /
		g_tile_size) % g_texture[index].width;
	while (wall->wall_top < wall->wall_bottom)
	{
		distance_from_top = wall->wall_top + (wall->wall_strip_height / 2) -
		(height / 2);
		offsetY = distance_from_top * ((float)g_texture[index].height /
		wall->wall_strip_height);
		texture_color = g_texture[index].wall_texture[([index].width *
		offsetY) + offsetX];
		g_image_data[(wall->wall_top * width) + i] = texture_color;
		wall->wall_top++;
	}
}

void	render_strip(t_data *data, t_ray *ray, int i)
{
	int	distance_projection_plane;


	distance_projection_plane = (width / 2) / tan(degToRad(fov) / 2);
	ray->distance *= cosf(ray->rang - degToRad(data->player.rotAng));
	ray->strip_height = (tile / ray->distance) * distance_projection_plane;
	ray->top = (height / 2) - (ray->strip_height / 2);
	if (ray->top  < 0)
		ray->top  = 0;
	ray->bottom = (height / 2) + (ray->strip_height / 2);
	if (ray->bottom > height)
		ray->bottom = height;
	draw_wall(data, ray, i);
}