/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 09:09:02 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 10:51:41 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

int	exit_cmd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	(void)cmd;
	(void)envp_ptr;
	return (last_exit_code);
}
