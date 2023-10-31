/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 22:23:45 by pferreir          #+#    #+#             */
/*   Updated: 2023/10/31 02:50:50 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	lenght(t_data *d, t_ray *ray)
{
	if (ray->hhit == 1)
		ray->LH = distance_between_points(d->px, d->py, ray->wall_hit_hx,
				ray->wall_hit_hy);
	else
		ray->LH = FLT_MAX;
	if (ray->vhit == 1)
		ray->LV = distance_between_points(d->px, d->py, ray->wall_hit_vx,
				ray->wall_hit_vy);
	else
		ray->LV = FLT_MAX;
	if (ray->LH < ray->LV)
	{
		ray->wall_hit_x = ray->wall_hit_hx;
		ray->wall_hit_y = ray->wall_hit_hy;
		ray->distance = ray->LH;
	}
	else
	{
		ray->wall_hit_x = ray->wall_hit_vx;
		ray->wall_hit_y = ray->wall_hit_vy;
		ray->distance = ray->LV;
	}
	if (ray->LV < ray->LH)
		ray->was_hit_vertical = 1;
}

void	vertical(t_data *d, t_ray *ray, int ang)
{
	float	next_vx;
	float	next_vy;
	int		tmp;

	ray->rang = degToRad(normalizeAngle(ang));
	ray->xintercept = floor(d->px / tile) * tile;
	if (ray->facing_right)
		ray->xintercept += tile;
	ray->yintercept = d->py + (ray->xintercept - d->px) * tan(ray->rang);
	ray->xstep = tile;
	if (ray->facing_left)
		ray->xstep *= -1;
	ray->ystep = tile * tan(ray->rang);
	if ((ray->facing_up && ray->ystep > 0) || (ray->facing_down
			&& ray->ystep < 0))
		ray->ystep *= -1;
	next_vx = ray->xintercept;
	next_vy = ray->yintercept;
	while (next_vx >= 0 && next_vx <= width && next_vy >= 0
		&& next_vy <= height)
	{
		tmp = 0;
		if (ray->facing_left)
			tmp = 1;
		if (is_wall(d, floor(next_vx / 64 - tmp), floor(next_vy / 64)))
		{
			ray->vhit = 1;
			return ;
		}
		else
		{
			next_vx += ray->xstep;
			next_vy += ray->ystep;
		}
	}
}

void	horizontal(t_data *d, t_ray *ray, int ang)
{
	float	next_hx;
	float	next_hy;
	int		tmp;

	ray->rang = degToRad(normalizeAngle(ang));
	ray->yintercept = floor(d->py / tile) * tile;
	if (ray->facing_down)
		ray->yintercept += tile;
	ray->xintercept = d->px + (ray->yintercept - d->py) / tan(ray->rang);
	ray->ystep = tile;
	if (ray->facing_up)
		ray->ystep *= -1;
	ray->xstep = tile / tan(ray->rang);
	if ((ray->facing_left && ray->xstep > 0) || (ray->facing_right
			&& ray->xstep < 0))
		ray->xstep *= -1;
	next_hx = ray->xintercept;
	next_hy = ray->yintercept;
	while (next_hx >= 0 && next_hx <= width && next_hy >= 0
		&& next_hy <= height)
	{
		tmp = 0;
		if (ray->facing_up)
			tmp = 1;
		if (is_wall(d, floor(next_hx / 64), floor(next_hy / 64 - tmp)))
		{
			ray->hhit = 1;
			return ;
		}
		else
		{
			next_hx += ray->xstep;
			next_hy += ray->ystep;
		}
	}
}

static int	choice_of_texture(t_ray *ray)
{
	if (ray->facing_up && !ray->was_hit_vertical)
		return (0);
	if (ray->facing_down && !ray->was_hit_vertical)
		return (1);
	if (ray->facing_left && ray->was_hit_vertical)
		return (2);
	if (ray->facing_right && ray->was_hit_vertical)
		return (3);
	(void)ray;
	return (0);
}

void	raycasting(t_data *d)
{
	int	i;

	i = 0;
	d->ray.rang = d->player.rotAng - (fov / 2);
	while (i < width)
	{
		ft_memset(&(d->ray), 0, sizeof(t_ray));
		facing_angle(&(d->ray));
		horizontal(d, &(d->ray), 90);
		vertical(d, &(d->ray), 90);
		lenght(d, &(d->ray));
		render_strip(d, &(d->ray), i);
		d->ray.rang += fov / width;
		i++;
	}
}



