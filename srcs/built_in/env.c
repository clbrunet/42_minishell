/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 07:10:30 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 10:53:00 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	env(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	char	**envp;

	(void)cmd;
	(void)last_exit_code;
	envp = *envp_ptr;
	while (*envp)
	{
		ft_putstr_fd(1, *envp);
		envp++;
	}
	return (0);
}
