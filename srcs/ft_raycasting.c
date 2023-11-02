/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:01:30 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/02 08:09:56 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_data *data, t_ray *ray, int x)
{
	int			y;
	int			n;

	y = 0;
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			n = W;
		else
			n = E;
	}
	else
	{
		if (ray->dir_y > 0)
			n = S;
		else
			n = N;
	}
	while(y < ray->start)
		img_pix_put(data->img, x, y++, data->ceiling_color);
	while (y < ray->end)
		img_pix_put(data->img, x, y++, data->texture[n]);
	while (y < HEIGHT - 1)
		img_pix_put(data->img, x, y++, data->floor_color);
}

void	init_raycasting(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->mapx = (int)player->px;
	ray->mapy = (int)player->py;
	ray->ddx = fabs(1 / ray->dir_x);
	ray->ddy = fabs(1 / ray->dir_y);
}

void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->stepx = -1;
		ray->sdx = (player->px - ray->mapx) * ray->ddx;
	}
	else
	{
		ray->stepx = 1;
		ray->sdx = (ray->mapx + 1.0 - player->px) * ray->ddx;
	}
	if (ray->dir_y < 0)
	{
		ray->stepy = -1;
		ray->sdy = (player->py - ray->mapy) * ray->ddy;
	}
	else
	{
		ray->stepy = 1;
		ray->sdy = (ray->mapy + 1.0 - player->py) * ray->ddy;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sdx < ray->sdy)
		{
			ray->sdx += ray->ddx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sdy += ray->ddy;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->mapy < 0.25 || ray->mapx < 0.25
			|| ray->mapy > data->nbline - 0.25
			|| ray->mapx > data->nbcol - 1.25)
			break ;
		else if (data->map[ray->mapy][ray->mapx] == '1')
			hit = 1;
	}
}

void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sdx - ray->ddx);
	else
		ray->wall_dist = (ray->sdy - ray->ddy);
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->start = -(ray->line_height) / 2 + HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = player->py + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->px + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	(void)data;
}

int	castAllRAys(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = data->ray;
	while (x < WIDTH)
	{
		init_raycasting(x, &ray, player);
		set_dda(&ray, player);
		perform_dda(data, &ray);
		calculate_line_height(&ray, data, player);
		draw_wall(data, &ray, x);
		x++;
	}
	return (1);
}