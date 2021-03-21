/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:59:05 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/21 08:20:04 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ft.h"

int		print_prompt(int last_exit_code)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putstr_fd(2, "minishell: getcwd failed\n");
		return (1);
	}
	ft_putstr_fd(1, "\x1B[1m" "\x1B[36m");
	ft_putstr_fd(1, cwd);
	if (last_exit_code == 0)
		ft_putstr_fd(1, "\x1B[32m" " $ " "\x1B[0m");
	else
		ft_putstr_fd(1, "\x1B[31m" " $ " "\x1B[0m");
	return (0);
}
