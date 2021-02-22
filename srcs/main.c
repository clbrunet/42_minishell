/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/22 08:25:30 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parsing.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*line;
	int		line_read;

	line_read = 1;
	while (line_read == 1)
	{
		if (print_prompt())
			return (1);
		line_read = get_next_line(&line);
	}
	if (line_read == -1)
		return (1);
	return (0);
}
