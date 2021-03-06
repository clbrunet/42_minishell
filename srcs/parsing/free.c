/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 08:59:28 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/21 11:03:07 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static unsigned	ft_lstsize_free_last(t_redirection *lst)
{
	t_redirection	*iter;
	unsigned		iter_nb;

	iter_nb = 0;
	iter = lst;
	while (iter->next)
	{
		iter_nb++;
		iter = iter->next;
	}
	free(iter->path_or_endstr);
	free(iter);
	return (iter_nb);
}

static void		free_cmd_redirections(t_redirection **lst)
{
	t_redirection	*iter;
	unsigned		iter_nb;
	unsigned		i;

	if (!lst || !*lst)
		return ;
	iter_nb = ft_lstsize_free_last(*lst);
	while (iter_nb)
	{
		iter = *lst;
		i = 0;
		while (i < iter_nb - 1)
		{
			iter = iter->next;
			i++;
		}
		free(iter->path_or_endstr);
		free(iter);
		iter_nb--;
	}
	*lst = (t_redirection *)NULL;
}

static void		free_one_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	free(cmd->exe);
	i = 0;
	while (cmd->args[i] != NULL)
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free_cmd_redirections(&cmd->in_redirection);
	free_cmd_redirections(&cmd->out_redirection);
	free(cmd);
}

void			free_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
		free_cmd(cmd->pipe);
		free_one_cmd(cmd);
	}
}
