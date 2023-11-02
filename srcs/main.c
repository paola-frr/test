/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:19:45 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 07:41:11 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->sdx = 0;
	ray->sdy = 0;
	ray->ddx = 0;
	ray->ddy = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->start = 0;
	ray->end = 0;
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	int		j;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 2)
		return (ft_printf("Wrong amount of arguments!\n"), 1);
	if (ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub\0", 5))
		return (ft_printf("It has to end with .cub!\n"), 1);
	if (parsing(&data, av[1]))
		return (1);
	i = 0;
	j = 0;
	data.nbline = data.h_map;
	data.nbcol = 0;
	while (i < data.nbline)
	{
		j = ft_strlen(data.work_map[i]);
		if (j >= data.nbcol)
			data.nbcol = j - 1;
		i++;
	}
	init_player(&data);
	init_game(&data);
	render_map(&data);
	key_handler(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	free_good_map(&data);
	return (0);
}
