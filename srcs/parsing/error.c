/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 18:02:26 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/08 17:06:38 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

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
	free(cmd);
}

t_cmd	*free_cmd_content(t_cmd *cmd, t_cmd *first_cmd)
{
	if (cmd != NULL)
	{
		free_cmd_content(cmd->pipe, first_cmd);
		if (cmd != first_cmd)
			free_cmd(cmd);
	}
	return (cmd);
}

void	free_cmds(t_cmd **cmds)
{
	int		i;

	i = 0;
	while (cmds[i] != NULL)
	{
		free_cmd_content(cmds[i], cmds[i]);
		free_cmd(cmds[i]);
		i++;
	}
	free(cmds);
}

int	syntax_error(char const *unexpected_token)
{
	ft_putstr_fd(2, "minishell: syntax error near unexpected token `");
	ft_putstr_fd(2, unexpected_token);
	ft_putstr_fd(2, "'\n");
	return (1);
}
