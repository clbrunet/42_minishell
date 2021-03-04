/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 07:10:30 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/04 07:42:29 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	env(t_cmd const *cmd, char **envp_ptr[])
{
	char	**envp;

	(void)cmd;
	envp = *envp_ptr;
	while (*envp)
	{
		ft_putstr_fd(1, *envp);
		envp++;
	}
	return (0);
}
