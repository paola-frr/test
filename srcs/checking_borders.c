/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_borders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:57:31 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/29 01:52:18 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	zero_or_letter(char c)
{
	if (c == '0')
		return (1);
	else if (c == 'N')
		return (1);
	else if (c == 'S')
		return (1);
	else if (c == 'E')
		return (1);
	else if (c == 'W')
		return (1);
	else
		return (0);
}

// void	len_map(t_data *data)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	data->len_map = 0;
// 	while (data->work_map[i] && i < data->h_map)
// 	{
// 		j = 0;
// 		while (data->work_map[i][j])
// 			j++;
// 		if (j > data->len_map)
// 			data->len_map = j;
// 		// printf("%d\n len now", data->len_map);
// 		i++;
// 	}
// }

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
	printf("%d\n", height);
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
		if (data->work_map[x][len - 1] == ' ' || data->work_map[x][len - 1] == '1' || data->work_map[x][len - 1] == '\n' || data->work_map[x][len - 1] == '\0')
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
		if (data->work_map[height][y] == ' ' || data->work_map[height][y] == '1' || data->work_map[height][y] == '\n')
			y++;
		else
			return (-1);
	}
	return (0);
}



int	check_borders(t_data *data)
{
	int	x;
	int	y;
	int	len;
	int	height;
	
	printf("%d\n", check_first_column(data));
	printf("%d\n", check_last_column(data));
	printf("%d\n", check_last_row(data));
	if (check_first_column(data) == -1 || check_last_column(data) == -1 || check_last_row(data) == -1)
		return (-1);
	x = 1;
	height = data->h_map - 1;
	while (data->work_map[x] && x < height)
	{
		len = ft_strlen(data->work_map[x]) - 1;
		y = 1;
		printf("row [%s], %d\n", data->work_map[x], len);
		while (data->work_map[x][y] && data->work_map[x - 1][y] && data->work_map[x + 1][y] && y < len)
		{
			if (data->work_map[x][y] == ' ' || data->work_map[x][y] == '1' || data->work_map[x][y] == '\n')
				y++;
			// else if ()
			else if (zero_or_letter(data->work_map[x][y]) && nospc(data->work_map[x - 1][y]) && nospc(data->work_map[x + 1][y]) &&
				nospc(data->work_map[x][y - 1]) && nospc(data->work_map[x][y + 1]))
				y++;
			else
				return (-1);
		}
		while (data->work_map[x][y] && ((ft_strlen(data->work_map[x - 1]) < len || ft_strlen(data->work_map[x + 1]) < len) ||
			(ft_strlen(data->work_map[x - 1]) < len && ft_strlen(data->work_map[x + 1]) < len)) && y < len)
		{
			if (zero_or_letter(data->work_map[x][y]))
				return (printf("this suka\n"), -1);
			else
				y++;
		}
		x++;
	}
	return (0);
}
