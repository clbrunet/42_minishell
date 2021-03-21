/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 09:09:02 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/21 07:51:15 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	exit_cmd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	int		i;

	(void)envp_ptr;
	if (cmd->args[1])
	{
		i = 0;
		if (cmd->args[1][0] == '-' || cmd->args[1][0] == '+')
			i = 1;
		while (ft_isdigit(cmd->args[1][i]))
			i++;
		if (cmd->args[1][i])
		{
			ft_putstr_fd(2, "minishell: exit: ");
			ft_putstr_fd(2, cmd->args[1]);
			ft_putstr_fd(2, ": numeric argument required\n");
			return (2);
		}
		if (cmd->args[2])
		{
			ft_putstr_fd(2, "minishell: exit: too many arguments\n");
			return (-1);
		}
		return ((unsigned char)ft_atoi(cmd->args[1]));
	}
	return (last_exit_code);
}
