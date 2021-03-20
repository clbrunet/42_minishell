/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:32:44 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/20 16:09:13 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	cd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	(void)envp_ptr;
	(void)last_exit_code;
	if (cmd->args[1] == NULL)
		ft_putstr_fd(2, "minishell: cd: relative or absolute path missing\n");
	else if (cmd->args[1][0] == '-' && cmd->args[1][1])
	{
		ft_putstr_fd(2, "minishell: cd: -");
		ft_putchar_fd(2, cmd->args[1][1]);
		ft_putstr_fd(2, ": invalid option\ncd: usage: cd [dir]\n");
		return (2);
	}
	else if (cmd->args[2])
		ft_putstr_fd(2, "minishell: cd: too many arguments\n");
	else if (chdir(cmd->args[1]))
	{
		ft_putstr_fd(2, "minishell: cd: ");
		ft_putstr_fd(2, cmd->args[1]);
		ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, strerror(errno));
		ft_putchar_fd(2, '\n');
	}
	else
		return (0);
	return (1);
}
