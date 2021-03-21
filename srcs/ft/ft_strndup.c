/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:49:28 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/21 10:04:41 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	char	*dup_bp;

	if (ft_strlen(s) > n)
		dup = malloc((n + 1) * sizeof(char));
	else
		dup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	dup_bp = dup;
	while (*s && n)
	{
		*dup = *s;
		dup++;
		s++;
		n--;
	}
	*dup = '\0';
	return (dup_bp);
}
