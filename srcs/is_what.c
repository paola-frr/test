/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_what.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:09:26 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/28 20:47:27 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_floor(t_data *data, char *s)
{
	int		i;
	char	**ithinkdifferent;
	int number = 0;
	int count = 0;
	
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != ',' && s[i] != '\t' && !ft_isdigit(s[i]) && s[i] != 'F' && s[i] != '\n')
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
			return (-1);
		count++;
	}
	free_dstr(ithinkdifferent);
	data->f_here++;
	return (1);
}

int	is_ceiling(t_data *data, char *s)
{
	int		i;
	char	**ithinkdifferent;
	int number = 0;
	int count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != ',' && s[i] != '\t' && !ft_isdigit(s[i]) && s[i] != 'C' && s[i] != '\n')
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
	ithinkdifferent = ft_split(&s[i], ',');
	if (!ithinkdifferent)
		return (-1);
	while (ithinkdifferent[count])
	{
		number = ft_atoi(ithinkdifferent[count]);
		if (count == 0 && number >= 0 && number <= 255)
			data->c_r = number;
		else if (count == 1 && number >= 0 && number <= 255)
			data->c_g = number;
		else if (count == 2 && number >= 0 && number <= 255)
			data->c_b = number;
		else
			return (-1);
		count++;
	}
	free_dstr(ithinkdifferent);
	data->c_here++;
	return (1);
}

int	valid_for_path(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '1' || s[i] == ' ' || s[i] == '\t')
			i++;;
	if (s[i] == '\n' || s[i] =='\0')
		return (0);
	while (s[i] && s[i] != '\n')
	{
		if (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '/' || s[i] == '.'|| s[i] == ' ' || s[i] == '\t')
			i++;
		else
			return (0);
	}
	if (s[i] == '\n' || s[i] =='\0')
		return (1);
	else
		return (0);
}


int	is_path(t_data *data, char *s)
{
	int i;
	int	no_spc;
	int	start;
	int	end;
	
	i = 0;
	no_spc = ft_strlen(s) - 1;
	if (!valid_for_path(s))
		return (0);
	if (s[no_spc] == '\n')
	{
		s[no_spc] = '\0';
		no_spc--;
	}
	while (s[no_spc] == ' ' || s[no_spc] == '\t')
		no_spc--;
	end = no_spc;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	data->tmp_path = malloc(sizeof(char) * (end + 2 - i));
	if (!data->tmp_path)
		return (0);
	start = 0;
	end -= i;
	while (i <= no_spc && start <= end)
	{
		data->tmp_path[start] = s[i];
		start++;
		i++;
	}
	data->tmp_path[start] = '\0';
	if (ft_strncmp(&data->tmp_path[ft_strlen(data->tmp_path) - 4], ".xpm\0", 5))
		return (0);
	start = 2;
	while (data->tmp_path[start] == ' ' || data->tmp_path[start] == '\t')
		start++;
	data->len_path = end - start + 1;
	while (end >= start)
	{
		if (data->tmp_path[start] == ' ' || data->tmp_path[start] == '\t')
			return (0);
		start++;
	}
	if (data->tmp_path[start] == '\0')
		return (1);
	return (0);
}

int	is_no(t_data *data)
{
	int		i;
	int		j;
	
	i = 2;
	if (data->tmp_path[0] != 'N')
		return (0);
	if (data->tmp_path[1] != 'O')
		return (0);
	while (data->tmp_path[i] == ' ' || data->tmp_path[i] == '\t')
		i++;
	data->no_path = malloc(sizeof(char *) * data->len_path);
	if (!data->no_path)
		return (0);
	j = 0;
	while (data->tmp_path[i] && data->tmp_path[i] != '\t' && data->tmp_path[i] != ' ')
	{
		data->no_path[j] = data->tmp_path[i];
		i++;
		j++;
	}
	data->no_path[j] = '\0';
	return (1);
}

int	is_so(t_data *data)
{
	int		i;
	int		j;
	
	i = 2;
	if (data->tmp_path[0] != 'S')
		return (0);
	if (data->tmp_path[1] != 'O')
		return (0);
	while (data->tmp_path[i] == ' ' || data->tmp_path[i] == '\t')
		i++;
	data->so_path = malloc(sizeof(char *) * data->len_path);
	if (!data->so_path)
		return (0);
	j = 0;
	while (data->tmp_path[i] && data->tmp_path[i] != '\t' && data->tmp_path[i] != ' ')
	{
		data->so_path[j] = data->tmp_path[i];
		i++;
		j++;
	}
	data->so_path[j] = '\0';
	return (1);
}

int	is_we(t_data *data)
{
	int		i;
	int		j;
	
	i = 2;
	if (data->tmp_path[0] != 'W')
		return (0);
	if (data->tmp_path[1] != 'E')
		return (0);
	while (data->tmp_path[i] == ' ' || data->tmp_path[i] == '\t')
		i++;
	data->we_path = malloc(sizeof(char *) * data->len_path);
	if (!data->we_path)
		return (0);
	j = 0;
	while (data->tmp_path[i] && data->tmp_path[i] != '\t' && data->tmp_path[i] != ' ')
	{
		data->we_path[j] = data->tmp_path[i];
		i++;
		j++;
	}
	data->we_path[j] = '\0';
	return (1);
}

int	is_ea(t_data *data)
{
	int		i;
	int		j;
	
	i = 2;
	if (data->tmp_path[0] != 'E')
		return (0);
	if (data->tmp_path[1] != 'A')
		return (0);
	while (data->tmp_path[i] == ' ' || data->tmp_path[i] == '\t')
		i++;
	data->ea_path = malloc(sizeof(char *) * data->len_path);
	if (!data->ea_path)
		return (0);
	j = 0;
	while (data->tmp_path[i] && data->tmp_path[i] != '\t' && data->tmp_path[i] != ' ')
	{
		data->ea_path[j] = data->tmp_path[i];
		i++;
		j++;
	}
	data->ea_path[j] = '\0';
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

