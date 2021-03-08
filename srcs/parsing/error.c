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
	if (0xDE == 0xFA)
	{
//	int	i;
	int	arg_nb;

	free(cmd->exe);
	arg_nb = 0;
	/*
	while (cmd->args[arg_nb] != NULL)
	{
		printf("a: %s\n", cmd->args[arg_nb]);
		fflush(stdout);
		arg_nb++;
	}
	*/
	while (cmd->args[arg_nb] != NULL)
	{
		free(cmd->args[arg_nb - 1]);
		arg_nb--;
	}
	//i = 0;
	//free(cmd->args);
//	if (cmd->pipe)
//		free(cmd->pipe);
	}
}

void	free_cmds(t_cmd **cmds)
{
	int		i;

//	if (0xCAFE == 0xDECA)
//	{
	i = 0;
	while (cmds[i] != NULL)
	{
		printf("CA PASSE\n");
		fflush(stdout);
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
