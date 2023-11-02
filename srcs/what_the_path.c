/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_the_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:19:19 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:28:01 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_no(t_data *data)
{
	int		i;
	int		j;

	i = 2;
	if (data->path[0] != 'N')
		return (0);
	if (data->path[1] != 'O')
		return (0);
	while (data->path[i] == ' ' || data->path[i] == '\t')
		i++;
	data->no_path = malloc(sizeof(char) * (data->len_path + 1));
	if (!data->no_path)
		return (0);
	j = 0;
	while (data->path[i] && data->path[i] != '\t' && data->path[i] != ' ')
	{
		data->no_path[j] = data->path[i];
		i++;
		j++;
	}
	data->no_path[j] = '\0';
	if (data->path)
		free(data->path);
	return (1);
}

int	is_so(t_data *data)
{
	int		i;
	int		j;

	i = 2;
	if (data->path[0] != 'S')
		return (0);
	if (data->path[1] != 'O')
		return (0);
	while (data->path[i] == ' ' || data->path[i] == '\t')
		i++;
	data->so_path = malloc(sizeof(char) * data->len_path + 1);
	if (!data->so_path)
		return (0);
	j = 0;
	while (data->path[i] && data->path[i] != '\t' && data->path[i] != ' ')
	{
		data->so_path[j] = data->path[i];
		i++;
		j++;
	}
	data->so_path[j] = '\0';
	if (data->path)
		free(data->path);
	return (1);
}

int	is_we(t_data *data)
{
	int		i;
	int		j;

	i = 2;
	if (data->path[0] != 'W')
		return (0);
	if (data->path[1] != 'E')
		return (0);
	while (data->path[i] == ' ' || data->path[i] == '\t')
		i++;
	data->we_path = malloc(sizeof(char) * data->len_path + 1);
	if (!data->we_path)
		return (0);
	j = 0;
	while (data->path[i] && data->path[i] != '\t' && data->path[i] != ' ')
	{
		data->we_path[j] = data->path[i];
		i++;
		j++;
	}
	data->we_path[j] = '\0';
	if (data->path)
		free(data->path);
	return (1);
}

int	is_ea(t_data *data)
{
	int		i;
	int		j;

	i = 2;
	if (data->path[0] != 'E')
		return (0);
	if (data->path[1] != 'A')
		return (0);
	while (data->path[i] == ' ' || data->path[i] == '\t')
		i++;
	data->ea_path = malloc(sizeof(char) * data->len_path + 1);
	if (!data->ea_path)
		return (0);
	j = 0;
	while (data->path[i] && data->path[i] != '\t' && data->path[i] != ' ')
	{
		data->ea_path[j] = data->path[i];
		i++;
		j++;
	}
	data->ea_path[j] = '\0';
	if (data->path)
		free(data->path);
	return (1);
}

int	set_path(t_data *data)
{
	if (is_no(data) && data->no_path)
		data->no_here++;
	else if (is_so(data) && data->so_path)
		data->so_here++;
	else if (is_ea(data) && data->ea_path)
		data->ea_here++;
	else if (is_we(data) && data->we_path)
		data->we_here++;
	else
		return (0);
	return (1);
}
