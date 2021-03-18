/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:04:47 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 18:34:29 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

#include <stdio.h>

int	export_cmd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	(void)cmd;
	(void)envp_ptr;
	(void)last_exit_code;

	printf("salut\n");
	fflush(stdout);
	*envp_ptr = malloc(sizeof(char **) * (2));
	envp_ptr[0][0] = ft_strdup("coucou");
	envp_ptr[0][1] = NULL;
	return (1);
}
