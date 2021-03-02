/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:36:01 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/02 06:28:21 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "built_in.h"
#include "ft.h"

built_in_ft	search_built_in(t_cmd const *cmd)
{
	if (ft_strcmp(cmd->exe, "echo") == 0)
		return (&echo);
	else if (ft_strcmp(cmd->exe, "cd") == 0)
		return (&cd);
	return (NULL);
}
