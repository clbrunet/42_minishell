/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:54:03 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 18:32:07 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*u_s1;
	const unsigned char	*u_s2;

	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while (*u_s1 && *u_s1 == *u_s2)
	{
		u_s1++;
		u_s2++;
	}
	return ((int)(*u_s1 - *u_s2));
}
