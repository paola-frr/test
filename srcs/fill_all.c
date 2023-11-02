/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:22:14 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:26:54 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	do_plus(t_data *data, int row)
{
	if (is_floor(data, data->map[row]) != -1
		|| is_ceiling(data, data->map[row]) != -1)
		return (1);
	else if (is_path(data, data->map[row]))
	{
		set_path(data);
		return (1);
	}
	else if (data->map[row][0] == '\n' || empty_row(data->map[row]))
		return (1);
	else
		return (0);
}

int	loop_all_stuff(t_data *data, int *row)
{
	while (data->map && data->map[*row])
	{
		if (do_plus(data, *row))
			(*row)++;
		else if (is_floor(data, data->map[*row]) == -1 && is_ceiling(data,
				data->map[*row]) == -1 && data->map[*row][0] != '\n'
			&& invalid_start(data, data->map[*row]) && !is_path(data,
			data->map[*row]))
			return (free_good_map(data), ft_printf("NOT VALID MAP\n"), -1);
		else if (invalid_start(data, data->map[*row]) == 0)
			return (0);
		else
			return (ft_printf("NOT VALID MAP\n"), -1);
	}
	return (0);
}

int	all_stuff_map(t_data *data)
{
	int	row;

	row = 0;
	while (data->map && data->map[row])
	{
		if (loop_all_stuff(data, &row) == -1)
			return (-1);
		if (invalid_start(data, data->map[row]) == 0)
		{
			data->work_map = check_map(data, row);
			if (!data->work_map)
				return (free_dstr(data->work_map), exit(0), -1);
			break ;
		}
		else
			return (ft_printf("NOT VALID MAP\n"), -1);
	}
	return (0);
}

int	check_all_inside(t_data *data)
{
	if (data->no_here != 1 || data->so_here != 1 || data->we_here != 1
		|| data->ea_here != 1 || data->c_here != 1 || data->f_here != 1)
	{
		free_good_map(data);
		return (printf("U miss something:(\n"), 0);
	}
	else
		return (1);
}
