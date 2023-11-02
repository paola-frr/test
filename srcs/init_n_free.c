/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:33:41 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:28:45 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	gnl_init(int fd, char **map)
{
	int		row;
	char	*tmp;

	row = 0;
	tmp = get_next_line(fd);
	if (!tmp)
		return (free(map), 1);
	while (tmp)
	{
		map[row] = ft_strdup(tmp);
		if (!tmp)
			return (1);
		if (tmp && !invalid_row(map[row]))
		{
			while (row >= 0)
				free(map[row--]);
			free(map);
			return (free(tmp), 1);
		}
		row++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	return (0);
}

int	init_map(t_data *data, int fd)
{
	char	**map;

	map = ft_calloc(sizeof(char *), (data->pheight) + 1);
	if (!map)
		return (1);
	if (gnl_init(fd, map))
		return (1);
	data->map = map;
	if (!data->map)
		return (free_dstr(data->map), free(map), close(fd), exit(0), 1);
	return (0);
}

void	init_whos_here(t_data *data)
{
	data->no_here = 0;
	data->so_here = 0;
	data->we_here = 0;
	data->ea_here = 0;
	data->c_here = 0;
	data->f_here = 0;
}

void	free_good_map(t_data *data)
{
	if (data->no_path)
		free(data->no_path);
	if (data->so_path)
		free(data->so_path);
	if (data->ea_path)
		free(data->ea_path);
	if (data->we_path)
		free(data->we_path);
	if (data->map)
		free_dstr(data->map);
	if (data->work_map)
		free_dstr(data->work_map);
}

void	free_dstr(char **dstr)
{
	int	i;

	i = 0;
	if (dstr == NULL)
		return ;
	while (dstr[i] != NULL)
	{
		free(dstr[i]);
		dstr[i] = NULL;
		i++;
	}
	free(dstr);
}
