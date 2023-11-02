/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:32:19 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:27:48 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	invalid_start(t_data *data, char *s)
{
	int	i;

	i = 0;
	if (s[0] == '\n')
		return (1);
	while (s[i])
	{
		if (s[i] == '1')
			data->cnt_1++;
		if (s[i] != ' ' && s[i] != '1' && s[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	invalid_row(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isascii(s[i]) || s[i] == '\n' || s[i] == '\0')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_valid_chars(t_data *data, char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
	{
		if (s[i] == '1' || s[i] == '0' || s[i] == ' ')
			i++;
		else if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
		{
			data->pos++;
			i++;
		}
		else
			return (0);
	}
	if (s[i] == '\n')
		return (1);
	return (0);
}

int	check_valid_char(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
	{
		if (s[i] == '1' || s[i] == '0' || s[i] == ' ' || s[i] == 'N'
			|| s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
			i++;
		else
			return (0);
	}
	if (s[i] == '\n')
	{
		return (1);
	}
	return (0);
}
