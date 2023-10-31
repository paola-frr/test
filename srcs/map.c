/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:21:29 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/28 23:39:33 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	height_of_map(int fd)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = get_next_line(fd);
	if (!tmp)
		return (printf("empty:(\n"), -1);
	if (!invalid_row(tmp))
		return (free(tmp), printf("What did you put in this map?! Invalid!\n"), 1);
	while (tmp)
	{
		i++;
		free(tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			return (i);
		// can i do it???
		if (tmp && !invalid_row(tmp))
			return (free(tmp), printf("What did you put in this map?! Invalid!\n"), 1);
	}
	return (i);
}

void	free_dstr(char **dstr)
{
	int	i;

	if (!dstr)
		return ;
	i = 0;
	while (dstr[i])
		free(dstr[i++]);
	free(dstr);
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
		if (s[i] == '1' || s[i] == '0' || s[i] == ' ' || s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
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


int	init_map(t_data *data, int fd)
{
	int			row;
	char		*tmp;
	char		**map;

	row = 0;
	int i = 0;
	map = ft_calloc(sizeof(char *), (data->height));
	if (!map)
		return (1);
	tmp = get_next_line(fd);
	if (!tmp)
		return (1);
	while (tmp && i < data->height)
	{
		map[row] = ft_strdup(tmp);
		if (!tmp)
			return (1);
		if (tmp && !invalid_row(map[row]))
			return (free(tmp), 1);
		row++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	data->map = map;
	if (!data->map)
		return (free_dstr(data->map), free(map), close(fd), exit(0), 1);
	return (0);
}


char **check_map(t_data *data, int cur_row)
{
	int			row;
	char		**map;

	row = 0;
	int i = 1;
	data->pos = 0;
	data->h_map = data->height - cur_row;
	map = ft_calloc(sizeof(char *), (data->h_map + 1));
	if (!map)
		return (NULL);
	if (invalid_start(data, data->map[cur_row]) == 0)
	{
		map[row] = ft_strdup(data->map[cur_row]);
		row++;
		cur_row++;
		while((i < data->h_map) && check_valid_char(data->map[cur_row]))
		{
			if (check_valid_chars(data, data->map[cur_row]) && i < data->h_map && data->pos < 2)
			{
				map[row] = ft_strdup(data->map[cur_row]);
				if (data->map[cur_row][0] == '\n' || data->map[cur_row][0] == '\0')
					return (printf("NOT VALID MAP\n"), free_dstr(map), NULL);
				// free_dstr(data->map) invalid
				row++;
				cur_row++;
				i++;
				if (i < data->h_map && data->map[cur_row] && !check_valid_char(data->map[cur_row]))
					return (printf("NOT VALID MAP\n"), free_dstr(map), NULL);
			}
			else
				return (printf("NOT VALID MAP\n"), free_dstr(map), NULL);
		}
		if (data->pos == 0)
			return (printf("NOT VALID MAP\n"), free_dstr(map), NULL);
	}
	else
		return (ft_printf("NOT VALID MAP\n"), NULL);
	return (map);
}


int	is_empty(t_data *data)
{
	int	row;
	
	row = 0;
	while (row < data->height)
	{
		if (data->map[row][0] == '\n')
			row++;
		else
			return (0);
	}
	return (printf("still empty:(\n"), exit (0), -1);
}

int	all_stuff_map(t_data *data)
{
	int			row;
	
	row = 0;
	while (data->map && data->map[row])
	{	
		while (data->map && data->map[row])
		{
			if (is_floor(data, data->map[row]) != -1)
			{
				row++;
			}
			else if (is_ceiling(data, data->map[row]) != -1)
			{
				row++;
			}
			else if (is_path(data, data->map[row]))
			{
				set_path(data);
				row++;
			}
			else if (data->map[row][0] == '\n')
				row++;
			else if (is_floor(data, data->map[row]) == -1 && is_ceiling(data, data->map[row]) == -1 && data->map[row][0] != '\n' &&  invalid_start(data, data->map[row]) && !is_path(data, data->map[row]))
				return (ft_printf("NOT VALID MAPeeee: (((((%s))))\n", data->map[row]), -1);
			else if (invalid_start(data, data->map[row]) == 0)
				break ;
			else
				return (ft_printf("NOT VALID MAPdddd\n"), -1);
		}
		if (invalid_start(data, data->map[row]) == 0)
		{
			data->work_map = check_map(data, row);
			if (!data->work_map)
				return (free_dstr(data->work_map), exit(0), -1);
			break ;
		}
		else
			return (ft_printf("NOT VALID MAPtttttt\n"), -1);
	}
	printf("%d\n", data->no_here);
	printf("%d\n", data->so_here);
	printf("%d\n", data->we_here);
	printf("%d\n", data->ea_here);
	printf("%d\n", data->c_here);
	printf("%d\n", data->f_here);
	return (0);
}

int	check_all_inside(t_data *data)
{
	if (data->no_here != 1)
		return (0);
	else if (data->so_here != 1)
		return (0);
	else if (data->we_here != 1)
		return (0);
	else if (data->ea_here != 1)
		return (0);
	else if (data->c_here != 1)
		return (0);
	else if (data->f_here != 1)
		return (0);
	else
		return (1);

}


int	parsing(t_data *data, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_printf("Not valid fd!\n"), exit(0));
	data->height = height_of_map(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_printf("Not valid fd!\n"), exit(0));
	if (init_map(data, fd))
		return (close(fd), 1);
	close(fd);
	if (is_empty(data))
		return (1);
	init_whos_here(data);
	if (all_stuff_map(data) == -1)
		return (1);
	if (!check_all_inside(data))
		return (1);
	if (check_borders(data) == -1)
		return (printf("kek not valid\n"), 1);
	printf("h %d\n", data->height);
	printf("h map %d\n", data->h_map);
	int k = 0;
	while (k < data->height)
	{
		printf("%s", data->map[k]);
		k++;
	}
	printf("\n\n\n\n\nMY MAP:\n");
	k = 0;
	while (k < data->h_map)
	{
		printf("%s", data->work_map[k]);
		k++;
	}
	printf("\n\n\n%d\n", data->f_r);
	printf("%d\n", data->f_g);
	printf("%d\n", data->f_b);
	printf("%d\n", data->c_r);
	printf("%d\n", data->c_g);
	printf("%d\n", data->c_b);
	



	printf("my path no: [[%s]]\n", data->no_path);
	printf("my path so: [[%s]]\n", data->so_path);
	printf("my path we: [[%s]]\n", data->we_path);
	printf("my path ea: [[%s]]\n", data->ea_path);
	
	return (0);
}

