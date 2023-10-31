/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 03:27:59 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/31 03:28:53 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_data *d, int l, int c)
{
	if (l < 0 || l > HEIGHT / 64 || c < 0 || c > WIDTH / 64)
		return (0);
	if (d->map[c][l] == '1')
		return (1);
	return (0);
}

float	degToRad(float ang)
{
	return (ang * M_PI / 180.0);
}

float	normalizeAngle(float angle)
{
	angle = remainderf(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void	facing_angle(t_ray *ray)
{
	if (ray->rang > 0 && ray->rang < M_PI)
		ray->facing_up = 1;
	else
		ray->facing_down = 1;
	if (ray->rang < 0.5 * M_PI || ray->rang > 1.5 * M_PI)
		ray->facing_right = 1;
	else
		ray->facing_left = 1;
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}