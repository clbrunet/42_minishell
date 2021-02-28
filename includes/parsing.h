/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 06:38:17 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 15:32:06 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "command.h"

int			get_next_line(char **line);

char const	*trim_inner_quotes(char const *line, char quote);
char		*str_substitute(char *str, char old, char new);

void		free_commands(t_command	**commands);
int			syntax_error(char const *unexpected_token);

int			check_command(char const *command, int len);

t_command	*parse_command(char const *command, int len);

int			check_line(char const *line);

t_command	**parse_line(char *line);


int			find_exec(char *envp[], char *cmd);

#endif
