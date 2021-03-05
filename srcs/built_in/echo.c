/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:25:09 by mlebrun           #+#    #+#             */
/*   Updated: 2021/02/28 18:33:03 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h" 
#include "ft.h"

/* args: temporary variable(need parsing): arguments and -n option */

int	echo(t_cmd *cmd)
{
	int		n_op = 1;
	int		i;

	(void)cmd;
	i = 0;
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(1, cmd->args[i]);
		ft_putchar_fd(1, ' ');
		i++;
	}
	if (n_op)
		ft_putchar_fd(1, '\n');
	return (1);
}
