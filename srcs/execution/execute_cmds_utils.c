/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:55:27 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 18:07:39 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void		free_pipes(int **pipes)
{
	int		**iter;

	if (pipes == NULL)
		return ;
	iter = pipes;
	while (*iter)
	{
		free(*iter);
		iter++;
	}
	free(pipes);
}

void		close_pipes_fds(int const *const *pipes)
{
	int const *const	*iter;

	if (pipes == NULL)
		return ;
	iter = pipes;
	while (*iter)
	{
		close((*iter)[0]);
		close((*iter)[1]);
		iter++;
	}
}

int			kill_cmd_processes(int *pids)
{
	while (*pids > 0)
	{
		if (kill(*pids, SIGKILL))
			return (1);
		pids++;
	}
	return (0);
}

static int	get_pipes_error(int ***pipes, int **iter)
{
	if (*iter)
	{
		free(*iter);
		*iter = NULL;
	}
	close_pipes_fds((int const *const *)*pipes);
	free_pipes(*pipes);
	*pipes = NULL;
	return (1);
}

int			get_pipes(int ***pipes, int len)
{
	int			**iter;

	*pipes = malloc((len + 1) * sizeof(int *));
	if (*pipes == NULL)
		return (1);
	iter = *pipes;
	while (len)
	{
		*iter = malloc(2 * sizeof(int));
		if (*iter == NULL || pipe(*iter) == -1)
			return (get_pipes_error(pipes, iter));
		iter++;
		len--;
	}
	*iter = NULL;
	return (0);
}
