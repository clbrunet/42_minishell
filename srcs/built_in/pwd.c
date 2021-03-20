/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 13:32:28 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 16:08:47 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int		pwd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	char	cwd[PATH_MAX];

	(void)envp_ptr;
	(void)last_exit_code;
	if (cmd->args[1] && cmd->args[1][0] == '-' && cmd->args[1][1])
	{
		ft_putstr_fd(2, "minishell: pwd: -");
		ft_putchar_fd(2, cmd->args[1][1]);
		ft_putstr_fd(2, ": invalid option\n");
		ft_putstr_fd(2, "pwd: usage: pwd\n");
		return (2);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	ft_putstr_fd(1, cwd);
	ft_putchar_fd(1, '\n');
	return (0);
}
