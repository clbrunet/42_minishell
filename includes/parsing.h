/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 06:38:17 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/27 14:33:30 by clbrunet         ###   ########.fr       */
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

int			get_next_line(char **line);

char const	*trim_inner_quotes(char const *line, char quote);
char const	*trim_inner_brackets(char const *line);

void		free_strs(char	**strs);
int			syntax_error(char const *unexpected_token);

int			check_line(char const *line);

char		**parse_line(char *line);

int			check_command(char const *command);

int			parse_commands(char **commands);

int			find_exec(char *envp[], char *cmd);

#endif
