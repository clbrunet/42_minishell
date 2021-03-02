/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:54:00 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/01 06:39:54 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	ft_lstsize(t_cmd const *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->pipe;
	}
	return (count);
}
