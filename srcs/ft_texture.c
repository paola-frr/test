/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:01:41 by pferreir          #+#    #+#             */
/*   Updated: 2023/11/02 06:59:12 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

static unsigned long	convert_rgb_to_hex(int r, int g, int b)
{
	unsigned long	result;

	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

void	init_texture(t_data *d)
{
	d->texture[N] = convert_rgb_to_hex(50, 50, 50);
	d->texture[S] = convert_rgb_to_hex(150, 0, 50);
	d->texture[E] = convert_rgb_to_hex(0, 50, 150);
	d->texture[W] = convert_rgb_to_hex(50, 150, 0);
}

// int	init_texture(t_data *d)
// {
// 	int	bpp;
// 	int	size_line;
// 	int	endian;
// 	int	i;

// 	i = 0;

// 	d->t[N].ptr = mlx_xpm_file_to_image(d->mlx,
// 		d->no_path, &d->t[N].width, &d->t[N].height);
// 	if (!d->t[N].ptr)
// 	{
// 		return (0);
// 	}
// 	d->t[N].wall = (int *)mlx_get_data_addr(d->t[N].ptr,
// 		&bpp, &size_line, &endian);
// 	if (!d->t[N].wall)
// 		return (0);

// 	d->t[S].ptr = mlx_xpm_file_to_image(d->mlx,
// 		d->so_path, &d->t[S].width, &d->t[S].height);
// 	if (!d->t[S].ptr)
// 	{
// 		return (0);
// 	}
// 	d->t[S].wall = (int *)mlx_get_data_addr(d->t[S].ptr,
// 		&bpp, &size_line, &endian);
// 	if (!d->t[S].wall)
// 		return (0);

// 	d->t[E].ptr = mlx_xpm_file_to_image(d->mlx,
// 		d->ea_path, &d->t[E].width, &d->t[E].height);
// 	if (!d->t[E].ptr)
// 	{
// 		return (0);
// 	}
// 	d->t[E].wall = (int *)mlx_get_data_addr(d->t[E].ptr,
// 		&bpp, &size_line, &endian);
// 	if (!d->t[E].wall)
// 		return (0);

// 	d->t[W].ptr = mlx_xpm_file_to_image(d->mlx,
// 		d->we_path, &d->t[W].width, &d->t[W].height);
// 	if (!d->t[W].ptr)
// 	{
// 		return (0);
// 	}
// 	d->t[W].wall = (int *)mlx_get_data_addr(d->t[W].ptr,
// 		&bpp, &size_line, &endian);
// 	if (!d->t[W].wall)
// 		return (0);
// 	return (1);
// }

// void	free_texture(t_data *d)
// {
// 	int	i;

// 	i = -1;
// 	if (d->t[0].path)
// 		free(d->t[0].path);
// 	if (d->t[1].path)
// 		free(d->t[1].path);
// 	if (d->t[2].path)
// 		free(d->t[2].path);
// 	if (d->t[3].path)
// 		free(d->t[3].path);
// 	if (d->t[0].ptr)
// 	{
// 		while (++i < 4)
// 		{
// 			if (d->t[i].ptr)
// 				mlx_destroy_image(d->mlx, d->t[i].ptr);
// 		}
// 	}
// }