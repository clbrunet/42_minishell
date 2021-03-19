/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:42:52 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/19 21:45:06 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int		is_name_valid_unset(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (i == 0 && (ft_isdigit(arg[i]) || (!ft_isalnum(arg[i])
			&& arg[i] != '_')))
		{
			return (0);
		}
		else if (i != 0 && !ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int		already_deleted(char **args, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (ft_strcmp(args[j], args[i]) == 0)
			return (1);
		j++;
	}
	return (0);
}
