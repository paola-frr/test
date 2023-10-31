/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 22:21:33 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/31 03:23:30 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	close_win(t_data *d)
{
	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	ft_freetab(d->map);
	exit (0);
	return (0);
}

int		key_pressed(t_player *player, int key_code)
{
	if (key_code == 119) //UP
		player->walkD = +1;
	else if (key_code == 115) //DOWN
		player->walkD = -1;
	else if (key_code == 65363) //RIGHT
		player->turnD = +1;
	else if (key_code == 65361) //LEFT
		player->turnD = -1;
	else if (key_code == 65307) //EXIT
		exit(free_all(1));
	else if (key_code == 100) //TRANSLATE R
	{
		player->translate = 1;
		player->walkD = +1;
	}
	else if (key_code == 97) //TRANSLATE  L
	{
		player->translate = -1;
		player->walkD = -1;
	}
	return (0);
}

int		key_release(t_player *player, int key_code)
{
	if (key_code == 119) //UP
		player->walkD = 0;
	else if (key_code == 115) //DOWN
		player->walkD = 0;
	else if (key_code == 65363) //RIGHT
		player->turnD = 0;
	else if (key_code == 65361) //LEFT
		player->turnD = 0;
	else if (key_code == 100|| key_code == 97) //TRANSLATE R || L
	{
		player->translate = 0;
		player->walkD = 0;
	}
	return (0);
}

int	render(t_data *data)
{
	data->player.moved += move_player(data);
	if (data->player.moved == 0)
		return (0);
	render_images(data);
	return (0);
}

void	start_game(t_data *data)
{
	player_movement(&(data->player));
	draw_background(data);
	raycasting(data);
	//mini map
	mlx_hook(data->win, 17, 1L << 17, &close_win, 0);
	mlx_hook(data->win, 2, (1L << 0), &key_pressed, 0);
	mlx_hook(data->win, 3, (1L << 1), &key_release, 0);
	mlx_loop_hook(data->mlx, render, &data);
	mlx_loop(data->mlx);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
}