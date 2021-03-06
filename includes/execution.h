/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 06:28:22 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 17:50:14 by clbrunet         ###   ########.fr       */
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
# include <errno.h>
# include <string.h>

# include "cmd.h"

void			free_pipes(int **pipes);
void			close_pipes_fds(int const *const *pipes);
int				kill_cmd_processes(int *pids);
int				get_pipes(int ***pipes, int len);
int				execute_cmd_error(int *pids, int **pipes);

int				redirect_stdin(char *endstr);
int				dup_io(t_cmd const *cmd, int **pipes, unsigned int i);

typedef int		(*t_built_in_ft)(t_cmd const *cmd, char **envp[],
		int last_exit_code);
t_built_in_ft	search_built_in(t_cmd const *cmd);

char			*create_path(char *sub_path, char *cmd);
char			*create_sub_path(char **envp, int i, int path_id,
		int *size_sub_path);

int				search_cmd(t_cmd const *cmd, char *envp[]);

int				pipeless_built_in(t_built_in_ft built_in_ft, t_cmd const *cmd,
		char **envp_ptr[], int last_exit_code);
int				cmd_process(int const *const *pipes, t_cmd const *cmd,
		char **envp_ptr[], int last_exit_code);
int				pipeless_cmd_process(t_cmd const *cmd, char **envp_ptr[]);
int				execute_cmds(char *line, char **envp_ptr[],
					int *last_exit_code);

#endif
