/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:59:05 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 19:58:03 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ft.h"

int		print_prompt(int last_exit_code)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	ft_putstr_fd(1, BOLD CYAN);
	ft_putstr_fd(1, cwd);
	if (last_exit_code == 0)
		ft_putstr_fd(1, GREEN " $ " RESET);
	else
		ft_putstr_fd(1, RED " $ " RESET);
	return (0);
}
