/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:04:29 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 20:03:25 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef enum					e_redirection_type
{
	NONE = 0,
	SIMPLE,
	DOUBLE
}								t_redirection_type;

typedef struct s_redirection	t_redirection;
struct							s_redirection
{
	t_redirection_type	type;
	char				*path_or_endstr;
	t_redirection		*next;
};

typedef struct s_cmd			t_cmd;
struct							s_cmd
{
	char			*exe;
	char			**args;
	t_redirection	*in_redirection;
	t_redirection	*out_redirection;
	t_cmd			*pipe;
};

typedef struct					s_parse_cmd
{
	t_cmd		*cmd;
	t_cmd		*p_cmd;
	t_cmd		*first_cmd;
	const char	*str_cmd;
	char		**envp;
	char		*buf;
	int			last_exit_code;
}								t_parse_cmd;

#endif
