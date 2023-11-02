/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borders_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:35:06 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:25:55 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	zero_or_letter(char c)
{
	if (c == '0')
		return (1);
	else if (c == 'N')
		return (2);
	else if (c == 'S')
		return (2);
	else if (c == 'E')
		return (2);
	else if (c == 'W')
		return (2);
	else
		return (0);
}

int	nospc(char c)
{
	if (c != ' ' && c != '\n' && c != '\t')
		return (1);
	return (0);
}

int	check_first_column(t_data *data)
{
	int	x;
	int	height;

	x = 0;
	height = data->h_map - 1;
	while (data->work_map[x] && x <= height)
	{
		if (data->work_map[x][0] == ' ' || data->work_map[x][0] == '1')
			x++;
		else
			return (-1);
	}
	return (0);
}

int	check_last_column(t_data *data)
{
	int	x;
	int	len;

	x = 0;
	while (data->work_map[x] && x < data->h_map)
	{
		len = ft_strlen(data->work_map[x]) - 1;
		if (data->work_map[x][len - 1] == ' '
			|| data->work_map[x][len - 1] == '1'
			|| data->work_map[x][len - 1] == '\n'
			|| data->work_map[x][len - 1] == '\0')
			x++;
		else
			return (-1);
	}
	return (0);
}

int	check_last_row(t_data *data)
{
	int	y;
	int	len;
	int	height;

	y = 0;
	height = data->h_map - 1;
	len = ft_strlen(data->work_map[height]) - 1;
	while (data->work_map[height][y] && y <= len)
	{
		if (data->work_map[height][y] == ' ' || data->work_map[height][y] == '1'
			|| data->work_map[height][y] == '\n')
			y++;
		else
			return (-1);
	}
	return (0);
}
