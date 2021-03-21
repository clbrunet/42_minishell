/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:25:09 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/21 08:15:51 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

static char	**trim_n_flag(char **iter, int *n_flag)
{
	int		i;

	*n_flag = 0;
	while (*iter && ft_strncmp(*iter, "-n", 2) == 0)
	{
		i = 2;
		while ((*iter)[i] == 'n')
			i++;
		if ((*iter)[i])
			return (iter);
		iter++;
		*n_flag = 1;
	}
	return (iter);
}

int			echo(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	int		n_flag;
	char	**iter;

	(void)envp_ptr;
	(void)last_exit_code;
	iter = trim_n_flag(cmd->args + 1, &n_flag);
	while (*iter != NULL)
	{
		ft_putstr_fd(1, *iter);
		iter++;
		if (*iter)
			ft_putchar_fd(1, ' ');
	}
	if (!n_flag)
		ft_putchar_fd(1, '\n');
	return (0);
}
