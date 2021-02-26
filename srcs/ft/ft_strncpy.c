/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:54:41 by mlebrun           #+#    #+#             */
/*   Updated: 2021/02/22 11:56:00 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft.h"

char	*ft_strncpy(char *dest, char const *src, int n)
{
	int		i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
