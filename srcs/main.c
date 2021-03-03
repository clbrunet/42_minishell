/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/01 13:48:26 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parsing.h"
#include "ft.h"
#include "built_in.h"
#include "cmd.h"

int	execute_cmds(t_cmd **cmds, char *envp[])
{
	int			(*built_in_ptr)(t_cmd *cmd);

	while (*cmds)
	{
		built_in_ptr = search_built_in(*cmds);
		if (built_in_ptr)
			(*built_in_ptr)(*cmds);
		else if (find_exec(envp, "pwd") == 0)
			ft_putstr_fd(1, "<inserted cmd>: cmd not found\n");
		cmds++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		line_read;
	t_cmd	**cmds;

	(void)argv;
	(void)envp;
	if (argc != 1)
		return (1);
	line_read = 1;
	while (line_read == 1)
	{
		if (print_prompt())
			return (1);
		line_read = get_next_line(&line);
		cmds = parse_line(line);
		free(line);
/*		if (cmds)
			execute_cmds(cmds, envp);
			*/
		free_cmds(cmds);
	}
	if (line_read == -1)
		return (1);
	return (0);
}
