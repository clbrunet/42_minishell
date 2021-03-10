/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:56:56 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/10 14:54:37 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "ft.h"

static int	redirect_input(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(2, path);
		ft_putstr_fd(2, strerror(errno));
		return (1);
	}
	else if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	redirect_stdin_end(int line_read, char *endstr)
{
	if (line_read == -1)
		return (1);
	else if (line_read == 0)
	{
		ft_putstr_fd(2, "minishell: warning: here-document delimited by "
				"end-of-file (wanted `");
		ft_putstr_fd(2, endstr);
		ft_putstr_fd(2, "')\n");
	}
	return (0);
}

static int	redirect_stdin(char *endstr)
{
	int		pipe_fds[2];
	char	*line;
	int		line_read;

	if (pipe(pipe_fds) == -1 || dup2(pipe_fds[0], STDIN_FILENO) == -1)
		return (1);
	close(pipe_fds[0]);
	ft_putstr_fd(1, "> ");
	line_read = get_next_line(&line);
	while (line_read == 1)
	{
		if (ft_strcmp(line, endstr) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(pipe_fds[1], line);
		ft_putstr_fd(pipe_fds[1], "\n");
		free(line);
		ft_putstr_fd(1, "> ");
		line_read = get_next_line(&line);
	}
	close(pipe_fds[1]);
	return (redirect_stdin_end(line_read, endstr));
}

static int	redirect_output(t_redirection redirection)
{
	int		fd;

	if (redirection.type == SIMPLE)
		fd = open(redirection.path_or_endstr, O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else
		fd = open(redirection.path_or_endstr, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
	{
		ft_putstr_fd(2, redirection.path_or_endstr);
		ft_putstr_fd(2, strerror(errno));
		return (1);
	}
	else if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	dup_pipes(t_cmd const *cmd, int **pipes, unsigned int i)
{
	if (cmd->in_redirection.type == SIMPLE)
	{
		if (redirect_input(cmd->in_redirection.path_or_endstr))
			return (1);
	}
	else if (cmd->in_redirection.type == DOUBLE)
	{
		if (redirect_stdin(cmd->in_redirection.path_or_endstr))
			return (1);
	}
	else if (i != 0 && dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		return (1);
	if (cmd->out_redirection.type != NONE)
	{
		if (redirect_output(cmd->out_redirection))
			return (1);
	}
	else if (cmd->pipe != NULL && dup2(pipes[i][1], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}
