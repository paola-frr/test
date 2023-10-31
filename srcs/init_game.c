/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:50:36 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/31 03:05:09 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	d->win = mlx_new_window(d->mlx, width, height, "depression3d");
	if (!d->win)
		return (0);
	d->img = mlx_new_image(d->mlx, width, height);
	if (!d->img)
		return (0);
	d->add = mlx_get_data_addr(d->img, &d->bits_per_pixel, &d->line_length,
		&d->endian);
	d->tex = ft_calloc(5, sizeof(d->tex));
	if (d->tex)
		return (0);
	// d->tex[N] = xpm_to_img();
	// d->tex[S] = xpm_to_img();
	// d->tex[E] = xpm_to_img();
	// d->tex[W] = xpm_to_img();
	// mlx_xpm_file_to_image
	//		mlx_mouse_move(data->mlx, data->win, data->win_width / 2, data->win_height / 2);
	return (1);
}

void	init_player(t_player *player)
{
	player->x = width / 2;
	player->y = height / 2;
	player->rad = 3;
	player->turnD = 0;
	player->walkD = 0;
	player->rotAng = 0.015;
	player->moveS = 0.0125;
	player->rotS = 2 * M_PI / 180;
}

void	init_game(t_data *d)
{
	if (!can_we_see_the_window(d))
	{
		ft_printf("MLX ERROR");
		return ;
	}
	start_game(d);
	mlx_loop_hook(d->mlx, &render, d);
	mlx_hook(d->win, 2, 1, &input_data, d);
	mlx_hook(d->win, 17, 0, &close_win, d);
	mlx_loop(d->mlx);
}

// unsigned int pixel = (coul.R<<16) | (coul.G<<8) | coul.B