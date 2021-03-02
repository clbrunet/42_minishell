/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 06:27:50 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/01 06:33:15 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft.h"

int	execute_cmds(t_cmd const *const *cmds, char *envp[])
{
	built_in_ft	built_in_ft;

	while (*cmds)
	{
		built_in_ft = search_built_in(*cmds);
		if (built_in_ft)
			(*built_in_ft)(*cmds);
		else if (find_exec(envp, "pwd") == 0)
			ft_putstr_fd(1, "<inserted cmd>: cmd not found\n");
		cmds++;
	}
	return (0);
}
