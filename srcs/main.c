/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/01 06:38:43 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ft.h"
#include "parsing.h"
#include "built_in.h"
#include "execution.h"

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
		if (cmds)
			execute_cmds((t_cmd const **)cmds, envp);
		free_cmds(cmds);
	}
	if (line_read == -1)
		return (1);
	return (0);
}
