/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/22 09:06:59 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parsing.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		line_read;

	(void)argc;
	(void)argv;
	(void)envp;
	line_read = 1;
	while (line_read == 1)
	{
		if (print_prompt())
			return (1);
		line_read = get_next_line(&line);
		printf("%s\n", line);
	}
	if (line_read == -1)
		return (1);
	return (0);
}
