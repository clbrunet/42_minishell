/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:56:56 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/08 16:41:57 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	dup_pipes(int **pipes, unsigned int i, t_cmd *pipe)
{
	if (i != 0 && dup2(pipes[i][1], STDIN_FILENO) == -1)
		return (1);
	if (pipe != NULL && dup2(pipes[i][0], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}
