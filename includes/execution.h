/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 06:28:22 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/02 06:27:46 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "cmd.h"

typedef int	(*built_in_ft)(t_cmd const *cmd);
built_in_ft	search_built_in(t_cmd const *cmd);

int			find_exec(char *envp[], char *cmd);

int			execute_cmds(t_cmd const *const *cmds, char *envp[]);

#endif
