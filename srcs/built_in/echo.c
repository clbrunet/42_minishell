/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:25:09 by mlebrun           #+#    #+#             */
/*   Updated: 2021/02/28 11:28:54 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "built_in.h" 

int		echo()
{
	/*temporary variable(need parsing): arguments and -n option*/
	char	*args[] = {"hello", "to", "you", NULL};
	int		n_op = 1;
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		ft_putstr_fd(1, args[i]);
		i++;
	}
	if (n_op)
		ft_putchar_fd(1, '\n');
	return (1);
}
