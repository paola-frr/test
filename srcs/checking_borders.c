/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_borders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:57:31 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:26:44 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_info(t_data *data, int x, int y)
{
	if (zero_or_letter(data->work_map[x][y]) == 2)
	{
		data->player_pos_x = x;
		data->player_pos_y = y;
		data->player_dir = data->work_map[x][y];
	}
}

int	longest_line_case(t_data *data, int x, int y, int len)
{
	while (data->work_map[x][y] && ((ft_strlen(data->work_map[x - 1]) < len
				|| ft_strlen(data->work_map[x + 1]) < len)
			|| (ft_strlen(data->work_map[x - 1]) < len
				&& ft_strlen(data->work_map[x + 1]) < len)) && y < len)
	{
		if (zero_or_letter(data->work_map[x][y]))
		{
			free_good_map(data);
			return (printf("Don't you dare:)\n"), -1);
		}
		else
			y++;
	}
	return (0);
}

int	process_checking(t_data *data, int x, int y, int len)
{
	while (data->work_map[x][y] && data->work_map[x - 1][y] && data->work_map[x
		+ 1][y] && y < len)
	{
		if (data->work_map[x][y] == ' ' || data->work_map[x][y] == '1'
			|| data->work_map[x][y] == '\n')
			y++;
		else if (zero_or_letter(data->work_map[x][y]) && nospc(data->work_map[x
					- 1][y]) && nospc(data->work_map[x + 1][y])
				&& nospc(data->work_map[x][y - 1]) && nospc(data->work_map[x][y
					+ 1]))
		{
			player_info(data, x, y);
			y++;
		}
		else
			return (-1);
	}
	if (longest_line_case(data, x, y, len) == -1)
		return (-1);
	return (0);
}

int	check_borders(t_data *data)
{
	int	x;
	int	y;
	int	len;
	int	height;

	if (check_first_column(data) == -1 || check_last_column(data) == -1
		|| check_last_row(data) == -1)
		return (-1);
	x = 1;
	height = data->h_map - 1;
	while (data->work_map[x] && x < height)
	{
		len = ft_strlen(data->work_map[x]) - 1;
		y = 1;
		if (process_checking(data, x, y, len) == -1)
			return (-1);
		x++;
	}
	return (0);
}
