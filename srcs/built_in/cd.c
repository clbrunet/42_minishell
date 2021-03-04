/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:32:44 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/04 07:23:54 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	cd(t_cmd const *cmd, char **envp_ptr[])
{
	(void)envp_ptr;
	if (cmd->args[1] == NULL)
	{
		ft_putstr_fd(2, "minishell: cd: relative or absolute path missing\n");
		return (1);
	}
	else if (cmd->args[2])
	{
		ft_putstr_fd(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	else if (chdir(cmd->args[1]))
		return (1);
	return (0);
}
