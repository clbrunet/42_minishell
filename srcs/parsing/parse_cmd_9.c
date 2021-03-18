/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:13:20 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/18 16:30:39 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void			real_no_quote_size(t_parse_cmd p, int *i, int *size, int len)
{
	int		to_escape;

	to_escape = 0;
	while (*i < len && p.str_cmd[*i] != ' ' && !(p.str_cmd[*i] == '|' &&
				!to_escape) && !(p.str_cmd[*i] == '>' && !to_escape)
			&& !(p.str_cmd[*i] == '<' && !to_escape))
	{
		if (p.str_cmd[*i] == '\\' && !to_escape)
			to_escape = 1;
		else
			to_escape = 0;
		*size = *size + 1;
		*i = *i + 1;
	}
}

void	skip_strings(char const *str, int *i, int len)
{
	while (str[*i] == '"' || str[*i] == '\'' || (*i < len && str[*i] != ' '
			&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>'))
	{
		if (str[*i] == '"')
			skip_quote(str, i);
		else if (str[*i] == '\'')
			skip_single_quote(str, i);
		else
			skip_no_quote(str, i, len);
	}
}

void	fill_single_quote(t_parse_cmd *p, int *i, int *j)
{
	*i = *i + 1;
	while (p->str_cmd[*i] != '\'')
	{
		p->buf[*j] = p->str_cmd[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	*i = *i + 1;
}

int		set_previous_pipe(t_parse_cmd *p, int *i)
{
	if (p->p_cmd)
		p->p_cmd->pipe = p->cmd;
	else
	{
		if (p->str_cmd[*i] != '|')
			return (0);
	}
	p->p_cmd = p->cmd;
	*i = *i + 1;
	return (1);
}

char	**parse_arguments(int *i, int size, int len, t_parse_cmd *p)
{
	int		arg_nb;
	char	**args;

	*i = *i + size;
	arg_nb = count_arg(p->str_cmd, *i, len);
	args = fill_args(p, i, len, arg_nb);
	if (!args)
		return (NULL);
	return (args);
}
