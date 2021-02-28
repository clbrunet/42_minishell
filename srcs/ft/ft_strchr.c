/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:47:28 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 11:31:57 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c_c;

	c_c = (char)c;
	while (*s && *s != c_c)
		s++;
	if (!c_c || *s == c_c)
		return ((char *)s);
	return ((char *) NULL);
}
