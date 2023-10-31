/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 03:19:16 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/31 03:32:05 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

static void	render_raycast(t_data *data)
{
	init_texture_pixels(data);
	init_ray(&data->ray);
	raycasting(&data->player, data);
	render_frame(data);
}

void	render_images(t_data *data)
{
	render_raycast(data);
	if (BONUS)
		render_minimap(data);
}

int	render(t_data *data)
{
	data->player.has_moved += move_player(data);
	if (data->player.has_moved == 0)
		return (0);
	render_images(data);
	return (0);
}

void	render_map(t_data *d)
{
	int	i;
	int	j;
	int	C;
	int	L;

	i = 0;
	C = 64 * d->nbcol;
	L = 64 * d->nbline;
	while (i < C)
	{
		j = 0;
		while (j < L)
		{
			if ((i - d->px) * (i - d->px) + (j - d->py) * (j - d->py) <= 20)
				img_pix_put(d->img, i, j++, 0xFF0000);
			else if ( i % 64  == 0 || j % 64 == 0)
				img_pix_put(d->img, i, j++, 0x000000);
			else if (d->map[j / 64][i / 64] == '1')
				img_pix_put(d->img, i, j++, 0x000000);
			else
				img_pix_put(d->img, i, j++, 0xFFFFFF);
		}
		++i;
	}
}

int	render(t_data *d)
{
	render_map(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (0);
}