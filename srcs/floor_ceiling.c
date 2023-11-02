/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:32:26 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:27:05 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_floor(t_data *data, char *s, int i)
{
	int		number;
	int		count;
	char	**ithinkdifferent;

	number = 0;
	count = 0;
	ithinkdifferent = ft_split(&s[i], ',');
	if (!ithinkdifferent)
		return (-1);
	while (ithinkdifferent[count])
	{
		number = ft_atoi(ithinkdifferent[count]);
		if (count == 0 && number >= 0 && number <= 255)
			data->f_r = number;
		else if (count == 1 && number >= 0 && number <= 255)
			data->f_g = number;
		else if (count == 2 && number >= 0 && number <= 255)
			data->f_b = number;
		else
			return (free_dstr(ithinkdifferent), -1);
		count++;
	}
	data->floor_color = data->f_r << 16 | data->f_g << 8 | data->f_b;
	free_dstr(ithinkdifferent);
	return (1);
}

int	is_floor(t_data *data, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != ',' && s[i] != '\t' && !ft_isdigit(s[i])
			&& s[i] != 'F' && s[i] != '\n')
			return (-1);
		i++;
	}
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] != 'F')
		return (-1);
	i++;
	if (s[i] != ' ')
		return (-1);
	if (loop_floor(data, s, i) == -1)
		return (-1);
	data->f_here++;
	return (1);
}

int	loop_ceiling(t_data *data, char *s, int i)
{
	int		cnt;
	int		number;
	char	**ithink;

	cnt = 0;
	number = 0;
	ithink = ft_split(&s[i], ',');
	if (!ithink)
		return (-1);
	while (ithink[cnt])
	{
		number = ft_atoi(ithink[cnt]);
		if (cnt == 0 && number >= 0 && number <= 255)
			data->c_r = number;
		else if (cnt == 1 && number >= 0 && number <= 255)
			data->c_g = number;
		else if (cnt == 2 && number >= 0 && number <= 255)
			data->c_b = number;
		else
			return (free_dstr(ithink), -1);
		cnt++;
	}
	data->ceiling_color = data->c_r << 16 | data->c_g << 8 | data->c_b;
	free_dstr(ithink);
	return (1);
}

int	is_ceiling(t_data *data, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != ',' && s[i] != '\t' && !ft_isdigit(s[i])
			&& s[i] != 'C' && s[i] != '\n')
			return (-1);
		i++;
	}
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] != 'C')
		return (-1);
	i++;
	if (s[i] != ' ')
		return (-1);
	if (loop_ceiling(data, s, i) == -1)
		return (-1);
	data->c_here++;
	return (1);
}
