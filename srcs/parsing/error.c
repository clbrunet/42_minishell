/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 18:02:26 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/06 18:40:56 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"
#include <stdio.h>
/* free structs */

void	free_cmds(t_cmd **cmds)
{
	int		i;
	int		j;
	t_cmd	*cmd;

//	if (0xCAFE == 0xDECA)
//	{
	printf("AH\n");
	fflush(stdout);
	i = 0;
	while (cmds[i] != NULL)
	{
		cmd = cmds[i];
		while (cmd != NULL)
		{
			free(cmd->exe);
			j = 0;
			while (cmd->args[j] != NULL)
			{
				free(cmd->args[j]);
				j++;
			}
			cmd = cmd->pipe;
		}
		free(cmds[i]->args[i]);
		i++;
	}
//	}
}

int	syntax_error(char const *unexpected_token)
{
	ft_putstr_fd(2, "minishell: syntax error near unexpected token `");
	ft_putstr_fd(2, unexpected_token);
	ft_putstr_fd(2, "'\n");
	return (1);
}
