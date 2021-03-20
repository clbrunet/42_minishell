/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:13:13 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/20 19:54:26 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

static int		determine_red_type(t_parse_cmd *p, int *i,
		t_redirection_type *red_type, int *in_out)
{
	if (p->str_cmd[*i] == '>')
		determine_in_type(p, in_out, i, red_type);
	else if (p->str_cmd[*i] == '<')
	{
		*in_out = 0;
		*i = *i + 1;
		if (p->str_cmd[*i] == '<')
		{
			*i = *i + 1;
			*red_type = DOUBLE;
		}
		else
			*red_type = SIMPLE;
	}
	else
		return (0);
	return (1);
}

static void		skip_char_red(t_parse_cmd *p, int *i, int len)
{
	int		to_escape;

	to_escape = 0;
	while (p->str_cmd[*i] == '"' || p->str_cmd[*i] == '\'' ||
			(*i < len && p->str_cmd[*i] != ' ' && p->str_cmd[*i] != '<'
			&& p->str_cmd[*i] != '>' && p->str_cmd[*i] != '|'))
		if (p->str_cmd[*i] == '"')
			skip_quote(p->str_cmd, i);
		else if (p->str_cmd[*i] == '\'')
			skip_single_quote(p->str_cmd, i);
		else
		{
			while ((p->str_cmd[*i] != ' ' && !(p->str_cmd[*i] == '>' &&
					!to_escape) && !(p->str_cmd[*i] == '<' && !to_escape) &&
					!(p->str_cmd[*i] == '|' && !to_escape)) && *i < len)
			{
				if (p->str_cmd[*i] == '\\' && !to_escape)
					to_escape = 1;
				else
					to_escape = 0;
				*i = *i + 1;
			}
		}
	while (p->str_cmd[*i] == ' ')
		*i = *i + 1;
}

static int		fill_redirection(t_parse_cmd *p, int *i, int len)
{
	int							in_out;
	t_redirection_type			red_type;

	in_out = 0;
	red_type = NONE;
	determine_red_type(p, i, &red_type, &in_out);
	while (1)
	{
		while (p->str_cmd[*i] == ' ')
			*i = *i + 1;
		if (red_type != 0)
		{
			p->buf = malloc(sizeof(char) *
			(size_component_formated(*p, *i, len) + 1));
			if (!p->buf)
				return (0);
			fill_buf(p, len, *i);
			add_red(p, p->buf, in_out, red_type);
		}
		red_type = NONE;
		skip_char_red(p, i, len);
		if (!determine_red_type(p, i, &red_type, &in_out))
			break ;
	}
	return (1);
}

static int		check_between_args(t_parse_cmd *p, int *i, int len)
{
	while (p->str_cmd[*i] == ' ')
		*i = *i + 1;
	if (p->str_cmd[*i] == '<' || p->str_cmd[*i] == '>')
		fill_redirection(p, i, len);
	if (p->str_cmd[*i] == '|' || p->str_cmd[*i] == '\0' || *i >= len)
		return (1);
	return (0);
}

char			**fill_args(t_parse_cmd *p, int *i, int len, int arg_nb)
{
	char		**args;
	int			size;
	int			j;

	args = init_args(arg_nb, *p);
	if (!args)
		return (0);
	j = 1;
	while (*i < len)
	{
		if (check_between_args(p, i, len))
			return (args);
		if (exist_if_dollar(p->str_cmd, *i, p->envp, len))
		{
			size = size_component_formated(*p, *i, len);
			p->buf = malloc(sizeof(char) * size + 1);
			if (!p->buf)
				return (NULL);
			fill_buf(p, len, *i);
			args[j] = p->buf;
			p->buf = NULL;
			*i = *i + real_component_size(*p, *i, len);
			j++;
		}
		else
			*i = *i + real_component_size(*p, *i, len);
	}
	return (args);
}
