/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:48:12 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/19 21:48:44 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int		is_only(char **args, int i)
{
	int		j;
	int		size_name;

	j = i + 1;
	while (args[j] != NULL)
	{
		size_name = size_env_name(args[i]);
		if (ft_strncmp(args[i], args[j], size_name) == 0)
			return (0);
		j++;
	}
	return (1);
}
