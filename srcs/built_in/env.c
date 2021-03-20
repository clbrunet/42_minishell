/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 07:10:30 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 16:23:28 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	env(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	char	**envp;

	(void)last_exit_code;
	if (cmd->args[1])
	{
		ft_putstr_fd(2, "minishell: env: too many arguments\n");
		return (1);
	}
	envp = *envp_ptr;
	while (*envp)
	{
		ft_putstr_fd(1, *envp);
		ft_putstr_fd(1, "\n");
		envp++;
	}
	return (0);
}
