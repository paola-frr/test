/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:09:26 by dsydelny          #+#    #+#             */
/*   Updated: 2023/11/02 05:26:21 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_for_path(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] == '1' || s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\n' || s[i] == '\0')
		return (0);
	j = i;
	while (s[j] && s[j] != '.')
		j++;
	if (ft_strncmp(&s[j], ".xpm", 4))
		return (0);
	while (s[i] && s[i] != '\n')
	{
		if (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '/' || s[i] == '.'
			|| s[i] == ' ' || s[i] == '\t')
			i++;
		else
			return (0);
	}
	if (s[i] == '\n' || s[i] == '\0')
		return (1);
	else
		return (0);
}

int	check_double_path(t_data *data, char *s, int i)
{
	if (data->so_path != NULL && !ft_strncmp(&s[i], "SO", 2))
		return (1);
	else if (data->no_path != NULL && !ft_strncmp(&s[i], "NO", 2))
		return (1);
	else if (data->ea_path != NULL && !ft_strncmp(&s[i], "EA", 2))
		return (1);
	else if (data->we_path != NULL && !ft_strncmp(&s[i], "WE", 2))
		return (1);
	else
		return (0);
}

int	skip_end(char *s)
{
	int	no_spc;

	no_spc = ft_strlen(s) - 1;
	if (s[no_spc] == '\n')
	{
		s[no_spc] = '\0';
		no_spc--;
	}
	while (s[no_spc] == ' ' || s[no_spc] == '\t')
		no_spc--;
	return (no_spc);
}

int	if_something(t_data *data, int end)
{
	int	start;

	if (ft_strncmp(&data->path[ft_strlen(data->path) - 4], ".xpm\0", 5))
		return (free(data->path), 0);
	start = 2;
	while (data->path[start] == ' ' || data->path[start] == '\t')
		start++;
	data->len_path = end - start + 1;
	while (end >= start)
	{
		if (data->path[start] == ' ' || data->path[start] == '\t')
			return (free_good_map(data), free(data->path),
				printf("Invalid path:(\n"), exit(0), 0);
		start++;
	}
	if (data->path[start] == '\0')
		return (1);
	if (data->path)
		free(data->path);
	return (0);
}

int	is_path(t_data *data, char *s)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	if (!valid_for_path(s))
		return (0);
	end = skip_end(s);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (check_double_path(data, s, i))
		return (0);
	data->path = malloc(sizeof(char) * (end + 2 - i));
	if (!data->path)
		return (0);
	start = 0;
	end -= i;
	while (i <= skip_end(s) && start <= end)
		data->path[start++] = s[i++];
	data->path[start] = '\0';
	if (if_something(data, end))
		return (1);
	return (0);
}
