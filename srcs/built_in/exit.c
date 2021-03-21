/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 09:09:02 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/21 09:54:56 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

static int	exit_with_args(char **args)
{
	int		i;

	i = 0;
	while (args[1][i] == ' ')
		i++;
	if (args[1][i] == '-' || args[1][i] == '+')
		i++;
	while (ft_isdigit(args[1][i]))
		i++;
	while (args[1][i] == ' ')
		i++;
	if (args[1][i])
	{
		ft_putstr_fd(2, "minishell: exit: ");
		ft_putstr_fd(2, args[1]);
		ft_putstr_fd(2, ": numeric argument required\n");
		return (2);
	}
	if (args[2])
	{
		ft_putstr_fd(2, "minishell: exit: too many arguments\n");
		return (-1);
	}
	return ((unsigned char)ft_atoi(args[1]));
}

int			exit_cmd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	(void)envp_ptr;
	if (cmd->args[1])
		return (exit_with_args(cmd->args));
	return (last_exit_code);
}
