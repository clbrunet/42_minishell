/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 18:31:50 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*parse_cmd(char const *str_cmd, int len)
{
	t_cmd	*cmd;

	if (check_cmd(str_cmd, len))
		return (NULL);
	cmd = NULL;
	return (cmd);
}
