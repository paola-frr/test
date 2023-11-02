/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RENDER.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:11:22 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/02 08:09:49 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_data *d)
{
	int i;
	int j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
			img_pix_put(d->img, j++, i + (HEIGHT / 2),d->floor_color);
		i++;
	}
}

void	draw_ceiling(t_data *d)
{
	int i;
	int j;

	i = 1;
	while (i < HEIGHT / 2)
	{
		j = 1;
		while (j < WIDTH)
			img_pix_put(d->img, j++, i,d->ceiling_color);
		i++;
	}
}

