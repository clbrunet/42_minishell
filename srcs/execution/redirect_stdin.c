/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_io2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 07:40:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 07:40:34 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include "ft.h"

static int	redirect_stdin_end(int pipe_fds[2], int line_read, char *endstr)
{
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		return (1);
	close(pipe_fds[0]);
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

int	redirect_stdin(char *endstr)
{
	int		pipe_fds[2];
	char	*line;
	int		line_read;

	if (pipe(pipe_fds) == -1)
		return (1);
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
	return (redirect_stdin_end(pipe_fds, line_read, endstr));
}
