/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PLAYER.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:58:55 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/02 06:24:17 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data)
{
	data->p.px = data->player_pos_x;
	data->p.py = data->player_pos_y;
	if (data->player_dir == 'S')
	{
		data->p.dir_x = 0;
		data->p.dir_y = 1;
		data->p.plane_x = -0.66;
		data->p.plane_y = 0;
	}
	else if (data->player_dir == 'N')
	{
		data->p.dir_x = 0;
		data->p.dir_y = -1;
		data->p.plane_x = 0.66;
		data->p.plane_y = 0;
	}
	if (data->player_dir == 'W')
	{
		data->p.dir_x = -1;
		data->p.dir_y = 0;
		data->p.plane_x = 0;
		data->p.plane_y = -0.66;
	}
	else if (data->player_dir == 'E')
	{
		data->p.dir_x = 1;
		data->p.dir_y = 0;
		data->p.plane_x = 0;
		data->p.plane_y = 0.66;
	}
}

int	rotate_player(double rotdir, t_player *p)
{
	int		moved;
	double tmp;
	double	rotspeed;

	moved = 0;
	rotspeed = rotS * rotdir;
	tmp = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
}

int	validate_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (new_x > 0.25 && new_x <= data->nbcol  * (tile - 1))
	{
		data->p.px = new_x;
		moved = 1;
	}
	if (new_y > 0.25 && new_y <= data->nbline * (tile - 1))
	{
		data->p.py = new_y;
		moved = 1;
	}
	return (moved);
}

int	move_player(t_data *data)
{
	double	new[2];

	if (data->p.move_y == 1)
	{
		new[0] = data->p.px + data->p.dir_x * moveS;
		new[1] = data->p.py + data->p.dir_y * moveS;
		printf("ox = %f oy = %f nx = %f ny = %f\n", data->p.px, data->p.py, new[0], new[1]);
	}
	else if (data->p.move_y == -1)
	{
		new[0] = data->p.px - data->p.dir_x * moveS;
		new[1] = data->p.py - data->p.dir_y * moveS;
	}
	else if (data->p.move_x == -1)
	{
		new[0] = data->p.px + data->p.dir_y * moveS;
		new[1] = data->p.py - data->p.dir_x * moveS;
	}
	else if (data->p.move_x == 1)
	{
		new[0] = data->p.px - data->p.dir_y * moveS;
		new[1] = data->p.py + data->p.dir_x * moveS;
	}
	else if (data->p.rot != 0)
		return(rotate_player(data->p.rot, &(data->p)));
	else
		return (0);
	return (validate_move(data, new[0], new[1]));
}
