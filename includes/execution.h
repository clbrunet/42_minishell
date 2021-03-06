/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 06:28:22 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/06 18:57:19 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

# include "cmd.h"

void			free_pipes(int **pipes);
void			close_pipes_fds(int const *const *pipes);
int				kill_cmd_processes(int *pids);
int				get_pipes(int ***pipes, int pipes_nb);
int				dup_pipes(int **pipes, unsigned int i, t_cmd *pipe);

typedef int		(*t_built_in_ft)(t_cmd const *cmd, char **envp[]);
t_built_in_ft	search_built_in(t_cmd const *cmd);

int				find_exec(char *envp[], char *cmd);

int				execute_cmds(char *line, char **envp_ptr[]);

#endif
