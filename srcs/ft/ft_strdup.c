/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:49:28 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/04 11:53:43 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*dup_bp;

	dup = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	dup_bp = dup;
	while (*s1)
	{
		*dup = *s1;
		dup++;
		s1++;
	}
	*dup = '\0';
	return (dup_bp);
}
