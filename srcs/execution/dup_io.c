/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:56:56 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 08:28:51 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft.h"

static int	redirect_input(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(2, "minishell: ");
		ft_putstr_fd(2, path);
		ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, strerror(errno));
		ft_putchar_fd(2, '\n');
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

static int	redirect_output(t_redirection *redirection)
{
	int		fd;

	if (redirection->type == SIMPLE)
		fd = open(redirection->path_or_endstr, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else
		fd = open(redirection->path_or_endstr, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
	{
		ft_putstr_fd(2, "minishell: ");
		ft_putstr_fd(2, redirection->path_or_endstr);
		ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, strerror(errno));
		ft_putchar_fd(2, '\n');
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

static int	dup_input(t_cmd const *cmd, int **pipes, unsigned int i)
{
	t_redirection	*iter;

	if (cmd->in_redirection)
	{
		iter = cmd->in_redirection;
		while (iter)
		{
			if ((iter->type == SIMPLE && redirect_input(iter->path_or_endstr))
				|| (iter->type == DOUBLE
						&& redirect_stdin(iter->path_or_endstr)))
				return (1);
			iter = iter->next;
		}
	}
	if (i != 0 && dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		return (1);
	return (0);
}

static int	dup_output(t_cmd const *cmd, int **pipes, unsigned int i)
{
	t_redirection	*iter;

	if (cmd->out_redirection)
	{
		iter = cmd->out_redirection;
		while (iter)
		{
			if (redirect_output(iter))
				return (1);
			iter = iter->next;
		}
	}
	if (cmd->pipe != NULL && dup2(pipes[i][1], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

int			dup_io(t_cmd const *cmd, int **pipes, unsigned int i)
{
	if (dup_input(cmd, pipes, i))
		return (1);
	if (dup_output(cmd, pipes, i))
		return (1);
	return (0);
}
