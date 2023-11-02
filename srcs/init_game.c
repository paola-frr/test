/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INIT_GAME.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:54:34 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/02 08:10:15 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	can_we_see_the_window(t_data *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		return (0);
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "cub3d");
	if (!d->win)
		return (0);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->img)
		return (0);
	d->add = mlx_get_data_addr(d->img, &d->bits_per_pixel, &d->line_length,
		&d->endian);
	if (!d->add)
		return (0);
	init_texture(d);
	return (1);
}

void	render_map2(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (i < d->nbcol * tile)
	{
		j = 0;
		while (j < d->nbline * tile)
		{
			// if ((i - hit_x) * (i - hit_x + (j - hit_y) * (j - hit_y) <= 20))
			// 	img_pix_put(d->img, i, j++, 0x0000FF);
			if ((i - d->p.px * tile) * (i - d->p.px * tile) + (j - d->p.py * tile) * (j - d->p.py * tile) <= 20)
				img_pix_put(d->img, i, j++, 0xFF0000);
			else if (i % tile  == 0 || j % tile == 0)
				img_pix_put(d->img, i, j++, 0x000000);
			else if (d->work_map[j / tile][i / tile] == '1')
				img_pix_put(d->img, i, j++, 0x000000);
			else
				img_pix_put(d->img, i, j++, 0xFFFFFF);
		}
		++i;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	// mlx_destroy_image(d->mlx, d->img);
}

int	render(t_data *data)
{
	if (!move_player(data))
		return (0);
	render_map(data);
	return (0);
}

// int	render2(t_data *d)
// {
// 	render_map2(d);
// 	return (0);
// }


void	render_map(t_data *d)
{
	castAllRAys(&(d->p), d);
	// draw_background(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

void	init_game(t_data *d)
{
	if (!can_we_see_the_window(d))
	{
		ft_printf("MLX ERROR");
		return ;
	}
}

int	close_window(t_data *d)
{
	if (d)
	{
		mlx_destroy_window(d->mlx, d->win);
	//	free_texture(d);
		mlx_destroy_image(d->mlx, d->img);
		mlx_destroy_display(d->mlx);
		mlx_loop_end(d->mlx);
		free(d->mlx);
	}
	exit (0);
	return (0);
}
