/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:16:40 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/23 14:53:41 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strndup(char const *s, size_t n)
{
	char	*dup;
	size_t	len;
	char	*dup_bp;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return ((char *) NULL);
	dup_bp = dup;
	while (len)
	{
		*dup = *s;
		dup++;
		s++;
		len--;
	}
	*dup = '\0';
	return (dup_bp);
}
