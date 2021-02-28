/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 07:22:47 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_command(char *command)
{
	if (check_command(command))
		return (1);
	return (0);
}

int	parse_commands(char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		if (parse_command(commands[i]))
			return (1);
		i++;
	}
	return (0);
}
