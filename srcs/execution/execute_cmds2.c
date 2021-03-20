/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:04:03 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 18:02:48 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft.h"

int	cmd_process(int const *const *pipes, t_cmd const *cmd,
		char **envp_ptr[], int last_exit_code)
{
	t_built_in_ft	built_in_ft;
	int				ret;

	close_pipes_fds(pipes);
	built_in_ft = search_built_in(cmd);
	if (built_in_ft)
		return ((*built_in_ft)(cmd, envp_ptr, last_exit_code));
	else
	{
		ret = search_cmd(cmd, *envp_ptr);
		if (ret == 0)
		{
			ft_putstr_fd(2, cmd->exe);
			ft_putstr_fd(2, ": command not found\n");
			return (127);
		}
		return (1);
	}
	return (0);
}

int	pipeless_built_in(t_built_in_ft built_in_ft, t_cmd const *cmd,
		char **envp_ptr[], int last_exit_code)
{
	int		std_fds[2];
	int		ret;

	std_fds[0] = dup(STDIN_FILENO);
	std_fds[1] = dup(STDOUT_FILENO);
	if (std_fds[0] == -1 || std_fds[1] == -1 || dup_io(cmd, NULL, 0))
		return (-1);
	ret = (*built_in_ft)(cmd, envp_ptr, last_exit_code);
	if (dup2(std_fds[0], STDIN_FILENO) == -1
		|| dup2(std_fds[1], STDOUT_FILENO) == -1)
		return (-1);
	close(std_fds[0]);
	close(std_fds[1]);
	return (ret);
}

int	pipeless_cmd_process(t_cmd const *cmd, char **envp_ptr[])
{
	if (dup_io(cmd, NULL, 0))
		return (1);
	if (search_cmd(cmd, *envp_ptr) == 0)
	{
		ft_putstr_fd(2, cmd->exe);
		ft_putstr_fd(2, ": command not found\n");
		return (127);
	}
	return (1);
}

int	execute_cmd_error(int *pids, int **pipes)
{
	free(pids);
	free_pipes(pipes);
	return (-1);
}
