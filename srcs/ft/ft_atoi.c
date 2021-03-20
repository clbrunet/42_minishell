/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:49:05 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 12:05:24 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\t'
			|| c == '\n' || c == '\r' || c == '\v');
}

int			ft_atoi(const char *str)
{
	long	n;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	n = 0;
	while (ft_isdigit(*str))
	{
		n = n * 10 + *str - '0';
		str++;
	}
	return (n * sign);
}
