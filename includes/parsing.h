/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 06:38:17 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 09:54:50 by clbrunet         ###   ########.fr       */
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
void		free_cmd(t_cmd *cmd);
t_cmd		*free_cmd_content(t_cmd *cmd, t_cmd *first_cmd);
int			syntax_error(char const *unexpected_token);

int			check_cmd(char const *cmd, int len);
int			check_line(char const *line);

t_cmd		**parse_line(char *line, char **envp[], int last_exit_code);
t_cmd		*parse_cmd(char const *cmd, int len, char **envp[],
			int last_exit_code);
int			size_component(t_parse_cmd p, int i, int len);
void		skip_redirection(char const *str, int *i, int len);
void		skip_no_quote(char const *str, int *i, int len);
void		skip_single_quote(char const *str, int *i);
void		skip_quote(char const *str, int *i);

int			count_arg(char const *str, int i, int len, char **envp);
int			size_var(t_parse_cmd p, int i, int j, int size_name);
int			fill_dollar(t_parse_cmd *p, int i, int *j, int to_escape);

int			is_meta_char(char c);
int			is_meta_char_quote(char c);
void		fill_quote(t_parse_cmd *p, int *i, int *j);
void		fill_no_quote(t_parse_cmd *p, int *i, int *j, int len);

void		fill_buf(t_parse_cmd *p, int len, int i);
char		**init_args(int	arg_nb, t_parse_cmd p);
int			real_component_size(t_parse_cmd p, int i, int len);

int			dollar_size(t_parse_cmd p, int *size, int *i, int to_escape);
void		size_quote(t_parse_cmd p, int *i, int *size);
int			size_component_formated(t_parse_cmd p, int i, int len);

void		add_red(t_parse_cmd *p, char *path_or_endstr, int in_out,
			t_redirection_type red_type);
void		determine_in_type(t_parse_cmd *p, int *in_out, int *i,
			t_redirection_type *red_type);

char		**fill_args(t_parse_cmd *p, int *i, int len, int arg_nb);

int			set_previous_pipe(t_parse_cmd *p, int *i);
char		**parse_arguments(int *i, int size, int len, t_parse_cmd *p);
void		fill_single_quote(t_parse_cmd *p, int *i, int *j);
void		skip_strings(char const *str, int *i, int len);
void		real_no_quote_size(t_parse_cmd p, int *i, int *size, int len);

#endif
