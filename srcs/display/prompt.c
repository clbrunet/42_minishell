/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:59:05 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/21 20:57:35 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

/*	Print prompt with the current working directory then a symbol '❯' to
	delimit from the command line.

	Return 1 if an error occurs. */

int	print_prompt(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	printf(CYAN "%s " GREEN "❯ \n" RESET, cwd);
	return (0);
}
