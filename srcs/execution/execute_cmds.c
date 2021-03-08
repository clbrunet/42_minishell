/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 06:27:50 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/06 17:36:16 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "ft.h"

static int	cmd_process(int const *const *pipes, t_cmd const *cmd,
		char **envp_ptr[])
{
	t_built_in_ft	built_in_ft;

	close_pipes_fds(pipes);
	built_in_ft = search_built_in(cmd);
	if (built_in_ft)
		return ((*built_in_ft)(cmd, envp_ptr));
	else if (find_exec(*envp_ptr, "pwd") == 0)
	{
		ft_putstr_fd(2, cmd->exe);
		ft_putstr_fd(2, ": command not found\n");
		return (1);
	}
	return (0);
}

static int	execute_cmd_end(t_cmd const *cmd, int *pids, unsigned int i,
		int **pipes)
{
	if (cmd && kill_cmd_processes(pids))
		return (1);
	else
	{
		while (i)
		{
			if (wait(NULL) == -1)
				return (1);
			i--;
		}
	}
	close_pipes_fds((int const *const *)pipes);
	free_pipes(pipes);
	return (0);
}

static int	execute_cmd(t_cmd const *cmd, int pipes_nb, char **envp_ptr[])
{
	int				*pids;
	int				**pipes;
	unsigned int	i;

	pids = malloc((pipes_nb + 1) * sizeof(int));
	if (pids == NULL || get_pipes(&pipes, pipes_nb))
		return (1);
	i = 0;
	while (cmd)
	{
		if (pipes && dup_pipes(pipes, i, cmd->pipe))
			return (1);
		pids[i] = fork();
		if (pids[i] == 0)
			exit(cmd_process((int const *const *)pipes, cmd, envp_ptr));
		else if (pids[i] == -1)
			break ;
		cmd = cmd->pipe;
		i++;
	}
	if (execute_cmd_end(cmd, pids, i, pipes))
		return (1);
	free(pids);
	return (0);
}

static int	execute_pipeless_cmd(t_cmd const *cmd, char **envp_ptr[])
{
	int				pid;
	t_built_in_ft	built_in_ft;

	built_in_ft = search_built_in(cmd);
	if (built_in_ft)
		return ((*built_in_ft)(cmd, envp_ptr));
	else
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid == 0)
		{
			if (find_exec(*envp_ptr, "pwd") == 0)
			{
				ft_putstr_fd(2, cmd->exe);
				ft_putstr_fd(2, ": command not found\n");
			}
			exit(1);
		}
		else if (wait(NULL) == -1)
			return (-1);
	}
	return (0);
}

int	execute_cmds(char *line, char **envp_ptr[])
{
	t_cmd	**cmds;
	t_cmd	**begin_cmds;

	cmds = parse_line(line);
	free(line);
	begin_cmds = cmds;
	while (*cmds)
	{
		if ((*cmds)->pipe)
		{
			if (execute_cmd(*cmds, ft_lstsize(*cmds) - 1, envp_ptr))
				return (1);
		}
		else if (execute_pipeless_cmd(*cmds, envp_ptr) == -1)
			return (1);
		cmds++;
	}
	free_cmds(begin_cmds);
	return (0);
}
