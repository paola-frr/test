/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:28:03 by dsydelny          #+#    #+#             */
/*   Updated: 2023/10/09 22:54:09 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_l(char a)
{
	return (write (2, &a, 1));
}

int	ft_putstr_l(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstr_l("(null)");
		return (6);
	}
	while (s[i])
	{
		ft_putchar_l(s[i]);
		i++;
	}
	return (i);
}
