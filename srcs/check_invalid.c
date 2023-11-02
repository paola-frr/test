/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:20:07 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:28:35 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_invalid_map(t_data *data, char **map)
{
	free_good_map(data);
	printf("NOT VALID MAP\n");
	free_dstr(map);
}

int	check_if_invalid(int row, t_data *data, int cur_row, char **map)
{
	int	i;

	i = 1;
	while ((i < data->h_map) && check_valid_char(data->map[cur_row]))
	{
		if (check_valid_chars(data, data->map[cur_row]) && i < data->h_map
			&& data->pos < 2)
		{
			map[row] = ft_strdup(data->map[cur_row]);
			if (data->map[cur_row][0] == '\n'
				|| data->map[cur_row][0] == '\0')
				return (error_invalid_map(data, map), 0);
			row++;
			cur_row++;
			i++;
			if (i < data->h_map && data->map[cur_row]
				&& !check_valid_char(data->map[cur_row]))
				return (error_invalid_map(data, map), 0);
		}
		else
			return (error_invalid_map(data, map), 0);
	}
	return (1);
}

char	**check_map(t_data *data, int cur_row)
{
	int		row;
	char	**map;

	row = 0;
	data->pos = 0;
	data->h_map = data->pheight - cur_row;
	map = ft_calloc(sizeof(char *), (data->h_map + 1));
	if (!map)
		return (NULL);
	if (invalid_start(data, data->map[cur_row]) == 0 && data->cnt_1 > 0)
	{
		map[row++] = ft_strdup(data->map[cur_row++]);
		if (!check_if_invalid(row, data, cur_row, map))
			return (NULL);
		if (data->pos == 0)
			return (error_invalid_map(data, map), NULL);
	}
	else
		return (free_good_map(data), ft_printf("NOT VALID MAP\n"), NULL);
	return (map);
}

int	is_empty(t_data *data)
{
	int	row;

	row = 0;
	while (row < data->pheight)
	{
		if (data->map[row][0] == '\n')
			row++;
		else
			return (0);
	}
	row = 0;
	while (row < data->pheight)
	{
		free(data->map[row]);
		row++;
	}
	free_good_map(data);
	return (printf("still empty:(\n"), exit(0), -1);
}

int	empty_row(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			return (0);
	}
	if (s[i] == '\n')
		return (1);
	return (0);
}
