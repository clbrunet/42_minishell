/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:36:01 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 18:32:29 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	(*search_built_in(t_cmd *cmd))(t_cmd *cmd)
{
	if (ft_strcmp(cmd->exe, "echo") == 0)
		return (&echo);
	return (NULL);
}
