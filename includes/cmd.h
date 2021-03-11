/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:04:29 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/10 15:31:02 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_cmd	t_cmd;
struct					s_cmd
{
	char	*exe;
	char	**args;
	t_cmd	*pipe;
};

typedef struct s_parse_cmd
{
	t_cmd		*cmd;
	t_cmd		*p_cmd;
	t_cmd		*first_cmd;
	const char	*str_cmd;
	char		**envp;
	char		*buf;

}	t_parse_cmd;

#endif
