/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:59:05 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/19 21:23:47 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	print_prompt(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	printf(CYAN "%s " GREEN "❯ " RESET, cwd);
	return (0);
}
