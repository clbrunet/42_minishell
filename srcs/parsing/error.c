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

void	free_cmd(t_cmd *cmd)
{
	int	i;

	free(cmd->exe);
	i = 0;
	while (cmd->args[i] != NULL)
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	if (cmd->pipe)
		free(cmd->pipe);
	free(cmd);

}


void	free_cmds(t_cmd **cmds)
{
	int		i;

//	if (0xCAFE == 0xDECA)
//	{

	i = 0;
	while (cmds[i] != NULL)
	{
		free_cmd(cmds[i]);
		i++;
	}
//	free(cmds);
//}
}



int	syntax_error(char const *unexpected_token)
{
	ft_putstr_fd(2, "minishell: syntax error near unexpected token `");
	ft_putstr_fd(2, unexpected_token);
	ft_putstr_fd(2, "'\n");
	return (1);
}
