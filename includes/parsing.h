/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 06:38:17 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/26 15:46:44 by mlebrun          ###   ########.fr       */
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

int		find_exec(char *envp[], char *cmd);

void	free_strs(char	**strs);
int		syntax_error(char const *unexpected_token);

char	**parse_line(char const *line);

int		get_next_line(char **line);

#endif
