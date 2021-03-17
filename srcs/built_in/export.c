/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:04:47 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 10:52:36 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"


#include <stdio.h>

int	export_cmd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	(void)cmd;
	(void)envp_ptr;
	(void)last_exit_code;
	printf("salut\n");
	fflush(stdout);
	return (1);
}
