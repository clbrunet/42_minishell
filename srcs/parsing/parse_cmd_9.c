/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:13:20 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/18 15:44:20 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		set_previous_pipe(t_parse_cmd *p, int *i)
{
	if (p->p_cmd)
		p->p_cmd->pipe = p->cmd;
	else
	{
		if (p->str_cmd[*i] != '|')
			return (0);
	}
	p->p_cmd = p->cmd;
	*i = *i + 1;
	return (1);
}

char	**parse_arguments(int *i, int size, int len, t_parse_cmd *p)
{
	int		arg_nb;
	char	**args;

	*i = *i + size;
	arg_nb = count_arg(p->str_cmd, *i, len);
	args = fill_args(p, i, len, arg_nb);
	if (!args)
		return (NULL);
	return (args);
}
