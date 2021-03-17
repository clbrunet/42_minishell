/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:12:43 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/17 16:07:34 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int				is_meta_char(char c)
{
	if (c == '>' || c == '<' || c == '*' || c == '?' || c == '['
		|| c == ']' || c == '|' || c == ';' || c == '&' || c == '('
		|| c == ')' || c == '#' || c == '$' || c == '\\' || c == '{'
		|| c == '}' || c == '"' || c == '\'' || c == '`' || c == ';'
		|| c == '=')
		return (1);
	return (0);
}

int				is_meta_char_quote(char c)
{
	if (c == '$' || c == '\\' || c == '"' || c == '`')
		return (1);
	return (0);
}

static void		add_char_quote(t_parse_cmd *p, int *i, int *j, int to_escape)
{
	if (!is_meta_char_quote(p->str_cmd[*i]) && to_escape)
	{
		p->buf[*j] = '\\';
		*j = *j + 1;
		p->buf[*j] = p->str_cmd[*i];
		*j = *j + 1;
	}
	else if (!is_meta_char_quote(p->str_cmd[*i]) ||
			(is_meta_char_quote(p->str_cmd[*i]) && to_escape))
	{
		p->buf[*j] = p->str_cmd[*i];
		*j = *j + 1;
	}
}

void			fill_quote(t_parse_cmd *p, int *i, int *j)
{
	int		to_escape;
	int		name_size;

	to_escape = 0;
	*i = *i + 1;
	while (!(p->str_cmd[*i] == '"' && !to_escape))
	{
		if (p->str_cmd[*i] == '\\' && !to_escape)
			to_escape = 1;
		else
		{
			add_char_quote(p, i, j, to_escape);
			name_size = fill_dollar(p, *i, j, to_escape);
			*i = *i + name_size;
			to_escape = 0;
		}
		*i = *i + 1;
	}
	*i = *i + 1;
}

void			fill_no_quote(t_parse_cmd *p, int *i, int *j, int len)
{
	int		to_escape;
	int		name_size;

	to_escape = 0;
	while (*i < len && p->str_cmd[*i] != ' ' &&
	!(p->str_cmd[*i] == '<' && !to_escape) && !(p->str_cmd[*i] == '>' &&
	!to_escape) && !(p->str_cmd[*i] == '|' && !to_escape))
	{
		if (p->str_cmd[*i] == '\\' && !to_escape)
			to_escape = 1;
		else
		{
			if (!is_meta_char(p->str_cmd[*i]) ||
			(is_meta_char(p->str_cmd[*i]) && to_escape))
			{
				p->buf[*j] = p->str_cmd[*i];
				*j = *j + 1;
			}
			name_size = fill_dollar(p, *i, j, to_escape);
			*i = *i + name_size;
			to_escape = 0;
		}
		*i = *i + 1;
	}
}
