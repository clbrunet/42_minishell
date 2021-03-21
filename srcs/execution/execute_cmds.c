/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 06:27:50 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/21 11:16:37 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "ft.h"
#include "main.h"

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
	pipes = NULL;
	if (pids == NULL || get_pipes(&pipes, len))
		return (execute_cmd_error(pids, pipes));
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (dup_io(cmd, pipes, i))
				return (execute_cmd_error(pids, pipes));
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
	if (cmd == NULL)
	{
		*last_exit_code = 2;
		return (2);
	}
	if (cmd->pipe)
		*last_exit_code = execute_cmd(cmd, ft_lstsize(cmd), envp_ptr,
				*last_exit_code);
	else
	{
		*last_exit_code = execute_pipeless_cmd(cmd, envp_ptr, *last_exit_code);
		if (ft_strcmp(cmd->exe, "exit") == 0 && *last_exit_code == -1)
		{
			*last_exit_code = 1;
			return (2);
		}
		else if (ft_strcmp(cmd->exe, "exit") == 0)
			return (1);
	}
	if (*last_exit_code == -1)
	{
		*last_exit_code = 130;
		return (2);
	}
	return (0);
}

int			execute_cmds(char *line, char **envp_ptr[], int *last_exit_code)
{
	char	**s_cmds;
	char	**s_cmds_backup;
	t_cmd	*cmd;
	int		ret;

	s_cmds = parse_line(line);
	free(line);
	if (s_cmds == NULL)
		return (0);
	s_cmds_backup = s_cmds;
	while (*s_cmds)
	{
		cmd = parse_cmd(*s_cmds, ft_strlen(*s_cmds), envp_ptr, *last_exit_code);
		if ((ret = execute_cmd_node(cmd, envp_ptr, last_exit_code)))
		{
			free_cmd(cmd);
			free_strs(s_cmds_backup);
			return ((ret == 2) ? 0 : 1);
		}
		free_cmd(cmd);
		s_cmds++;
	}
	free_strs(s_cmds_backup);
	return (0);
}
