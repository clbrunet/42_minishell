/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 06:27:50 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 11:10:59 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "ft.h"

static int	execute_cmd_end(t_cmd const *cmd, int *pids, unsigned int i,
		int **pipes)
{
	int		wstatus;

	close_pipes_fds((int const *const *)pipes);
	if (cmd && kill_cmd_processes(pids))
		return (-1);
	else
	{
		while (i)
		{
			if (wait(&wstatus) == -1)
				return (-1);
			i--;
		}
	}
	free(pids);
	free_pipes(pipes);
	if (!WIFEXITED(wstatus))
		return (-1);
	return (WEXITSTATUS(wstatus));
}

static int	execute_cmd(t_cmd const *cmd, int len, char **envp_ptr[],
		int last_exit_code)
{
	int				*pids;
	int				**pipes;
	unsigned int	i;

	pids = malloc((len) * sizeof(int));
	if (pids == NULL || get_pipes(&pipes, len))
		return (-1);
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (dup_io(cmd, pipes, i))
				return (-1);
			exit(cmd_process((int const *const *)pipes, cmd, envp_ptr,
						last_exit_code));
		}
		else if (pids[i] == -1)
			break ;
		cmd = cmd->pipe;
		i++;
	}
	return (execute_cmd_end(cmd, pids, i, pipes));
}

static int	execute_pipeless_cmd(t_cmd const *cmd, char **envp_ptr[],
		int last_exit_code)
{
	int				pid;
	t_built_in_ft	built_in_ft;
	int				wstatus;

	built_in_ft = search_built_in(cmd);
	if (built_in_ft)
		return (pipeless_built_in(built_in_ft, cmd, envp_ptr, last_exit_code));
	else
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid == 0)
			exit(pipeless_cmd_process(cmd, envp_ptr));
		else if (wait(&wstatus) == -1 || !WIFEXITED(wstatus))
			return (-1);
	}
	return (WEXITSTATUS(wstatus));
}

static int	execute_cmd_node(t_cmd *cmd, char **envp_ptr[],
		int *last_exit_code)
{
	if (cmd->pipe)
		*last_exit_code = execute_cmd(cmd, ft_lstsize(cmd), envp_ptr,
				*last_exit_code);
	else
	{
		if (ft_strcmp(cmd->exe, "exit") == 0)
			return (1);
		*last_exit_code = execute_pipeless_cmd(cmd, envp_ptr, *last_exit_code);
	}
	return (0);
}

int			execute_cmds(char *line, char **envp_ptr[], int *last_exit_code)
{
	t_cmd	**cmds;
	t_cmd	**begin_cmds;

	cmds = parse_line(line, envp_ptr);
	free(line);
	if (cmds == NULL)
		return (0);
	begin_cmds = cmds;
	while (*cmds)
	{
		if (execute_cmd_node(*cmds, envp_ptr, last_exit_code))
		{
			free_cmds(begin_cmds);
			return (1);
		}
		else if (*last_exit_code == -1)
		{
			free_cmds(begin_cmds);
			return (-1);
		}
		cmds++;
	}
	free_cmds(begin_cmds);
	return (0);
}
