/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:21:29 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:45:12 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	height_of_map(int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = get_next_line(fd);
	if (!tmp)
		return (printf("nothing to read:(\n"), -1);
	if (!invalid_row(tmp))
		return (free(tmp), printf("What did you put in this map?!\n"), 1);
	while (tmp)
	{
		i++;
		free(tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			return (i);
		if (tmp && !invalid_row(tmp))
			return (free(tmp),
				printf("What did you put in this map?!\n"), 1);
	}
	free(tmp);
	return (i);
}

int	parsing(t_data *data, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_printf("Not valid fd!\n"), exit(0));
	data->pheight = height_of_map(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_printf("Not valid fd!\n"), exit(0));
	if (init_map(data, fd))
		return (close(fd), 1);
	close(fd);
	if (is_empty(data))
		return (1);
	init_whos_here(data);
	if (all_stuff_map(data) == -1 || !check_all_inside(data))
		return (1);
	if (check_borders(data) == -1)
	{
		free_good_map(data);
		return (ft_printf("We have problems with borders!\n"), 1);
	}
	int k = 0;
	// while (k < data->pheight)
	// {
	// 	printf("%s", data->map[k]);
	// 	k++;
	// }
	// printf("\n\n\n\n\nMY MAP:\n");
	// k = 0;
	while (k < data->h_map)
	{
		printf("%s", data->work_map[k]);
		k++;
	}
	/*printf("\n\n\n%d\n", data->f_r);
	printf("%d\n", data->f_g);
	printf("%d\n", data->f_b);
	printf("%d\n", data->c_r);
	printf("%d\n", data->c_g);
	printf("%d\n", data->c_b);
	

	printf("floor: %lu\n", data->floor_color);
	printf("ceil: %lu\n", data->ceiling_color);

	printf("my path no: [[%s]]\n", data->no_path);
	printf("my path so: [[%s]]\n", data->so_path);
	printf("my path we: [[%s]]\n", data->we_path);
	printf("my path ea: [[%s]]\n", data->ea_path);
	
	printf("x [%d]\n", data->player_pos_x);
	printf("y [%d]\n", data->player_pos_y);
	printf(" dir [%c]\n", data->player_dir);*/
	return (0);
}
