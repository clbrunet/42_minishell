/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 06:38:17 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 18:34:49 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>

# include "cmd.h"

int			get_next_line(char **line);

char const	*trim_inner_quotes(char const *line, char quote);
char		*str_substitute(char *str, char old, char new);

void		free_cmds(t_cmd	**cmds);
int			syntax_error(char const *unexpected_token);

int			check_cmd(char const *cmd, int len);

t_cmd		*parse_cmd(char const *cmd, int len);

int			check_line(char const *line);

t_cmd		**parse_line(char *line);

#endif
