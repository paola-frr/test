/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:36:20 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/31 03:42:02 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#include "cub3d.h"

int		orientation(float angle)
{
	angle = normalize_angle(angle);
	if ((angle > M_PI * 0.25) && (angle < 0.75 * M_PI))
		return (1);
	else if ((angle > M_PI * 1.25) && (angle < 1.75 * M_PI))
		return (1);
	return (0);
}

void			player_movement(t_player *player)
{
	float		move_step;
	float		newX;
	float		newY;
	int			orientation;

	orientation = orientation(player->rotAng);

	player->rotAng += player->turnD * player->rotS;

	move_step = player->walkD * player->move_speed;

	newX = player->x + cos(player->rotAng) * move_step;

	newY = player->y + sin(player->rotAng) * move_step;
	
	if (player->translate == -1 || player->translate == 1)
	{
		player->angle_angle = (M_PI * 0.5) - player->rotAng;
		if (orientation == 1)
		{
			newX = player->x - cos(player->angle_angle) * move_step;
			newY = player->y + sin(player->angle_angle) * move_step;
		}
		else if (orientation == 0)
		{
			newX = player->x + cos(player->angle_angle) * -move_step;
			newY = player->y - sin(player->angle_angle) * -move_step;
		}
	}
}

/*void			player_movement(t_player *player)
{
	float		move_step;
	float		newX;
	float		newY;
	int			orientation;

	orientation = orientation(player->rotAng);

	player->rotAng += player->turnD * player->rotS;

	move_step = player->walkD * player->move_speed;

	newX = player->x + cos(player->rotAng) * move_step;

	newY = player->y + sin(player->rotAng) * move_step;
	
	if (player->translate == -1 || player->translate == 1)
	{
		player->angle_angle = (M_PI * 0.5) - player->rotAng;
		if (orientation == 1)
		{
			newX = player->x - cos(player->angle_angle) * move_step;
			newY = player->y + sin(player->angle_angle) * move_step;
		}
		else if (orientation == 0)
		{
			newX = player->x + cos(player->angle_angle) * -move_step;
			newY = player->y - sin(player->angle_angle) * -move_step;
		}
	}
}*/
