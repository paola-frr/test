/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:19:45 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/31 03:21:08 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_whos_here(t_data *data)
{
	data->no_here = 0;
	data->so_here = 0;
	data->we_here = 0;
	data->ea_here = 0;
	data->c_here = 0;
	data->f_here = 0;
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(& data, 0, sizeof(t_data));
	if (ac != 2)
		return (ft_printf("Wrong amount of arguments!\n"), 1);
	if (ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub\0", 5))
		return (ft_printf("It has to end with .cub!\n"), 1);
	if (parsing(&data, av[1]))
		return (1);

	while (data.map && data.map[data.nbline])
	{
		if ((int)ft_strlen(data.map[data.nbline]) != data.nbcol)
			return (0);
		data.nbline++;
	}
	data.px = data.nbcol * 32;
	data.py = (data.nbline - 3) * 32;
	init_player(&(data.player));
	init_game(&data);
	// init game
	return (0);
}

// check first column, last row, last colum
//handle spaces after xpm
// floor ceill - can be spaces between r g b??
// give to paola clear path to img
