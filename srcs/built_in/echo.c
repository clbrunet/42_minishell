/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:25:09 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/06 12:14:16 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	echo(t_cmd const *cmd, char **envp_ptr[])
{
	int		n_flag;
	char	**iter;

	(void)envp_ptr;
	iter = cmd->args + 1;
	if (ft_strcmp(*iter, "-n") == 0)
	{
		iter++;
		n_flag = 1;
	}
	else
		n_flag = 0;
	while (*iter != NULL)
	{
		ft_putstr_fd(1, *iter);
		ft_putchar_fd(1, ' ');
		iter++;
	}
	if (!n_flag)
		ft_putchar_fd(1, '\n');
	return (1);
}
