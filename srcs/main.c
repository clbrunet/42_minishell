/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 07:32:41 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parsing.h"
#include "ft.h"
#include <errno.h>

void	print_free_commands(char **commands)
{
	char	**iter;

	if (parse_commands(commands))
		return ;
	iter = commands;
	while (*iter)
	{
		printf("|%s|\n", *iter);
		free(*iter);
		iter++;
	}
	free(commands);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		line_read;
	char	**commands;

	(void)argc;
	(void)argv;
	(void)envp;
	line_read = 1;
	while (line_read == 1)
	{
		if (print_prompt())
			return (1);
		line_read = get_next_line(&line);
		commands = parse_line(line);
		free(line);
		find_exec(envp, "pwd");
		if (commands)
			print_free_commands(commands);
	}
	if (line_read == -1)
		return (1);
	return (0);
}
