/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 17:28:03 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	main_error(int ret, char *envp[], int last_exit_code)
{
	free_strs(envp);
	if (ret == 1)
	{
		ft_putstr_fd(1, "exit\n");
		return ((unsigned char)last_exit_code);
	}
	return (1);
}

static int	main_end(int line_read, char *envp[], int last_exit_code)
{
	free_strs(envp);
	if (line_read == -1)
		return (1);
	ft_putstr_fd(1, "exit\n");
	return ((unsigned char)last_exit_code);
}

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		line_read;
	int		last_exit_code;
	int		ret;

	(void)argv;
	last_exit_code = 0;
	if (argc != 1 || signal(SIGINT, &reading_int_handler) == SIG_ERR
			|| signal(SIGQUIT, &reading_quit_handler) == SIG_ERR
			|| print_prompt(last_exit_code) || malloc_envp(&envp))
		return (1);
	line_read = get_next_line(&line);
	while (line_read == 1)
	{
		if (signal(SIGINT, &execution_int_handler) == SIG_ERR
				|| signal(SIGQUIT, &execution_quit_handler) == SIG_ERR)
			return (main_error(0, envp, 0));
		ret = execute_cmds(line, &envp, &last_exit_code);
		if (ret || print_prompt(last_exit_code)
				|| signal(SIGINT, &reading_int_handler) == SIG_ERR
				|| signal(SIGQUIT, &reading_quit_handler) == SIG_ERR)
			return (main_error(ret, envp, last_exit_code));
		line_read = get_next_line(&line);
	}
	return (main_end(line_read, envp, last_exit_code));
}
