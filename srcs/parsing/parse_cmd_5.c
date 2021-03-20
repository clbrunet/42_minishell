/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:12:50 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/20 21:03:31 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <ft.h>

void			fill_buf(t_parse_cmd *p, int len, int i)
{
	int		to_escape;
	int		j;

	j = 0;
	to_escape = 0;
	while (p->str_cmd[i] == '"' || p->str_cmd[i] == '\'' ||
			(p->str_cmd[i] != ' ' && p->str_cmd[i] != '<'
			&& p->str_cmd[i] != '>' && p->str_cmd[i] != '|' && i < len))
	{
		if (p->str_cmd[i] == '"')
			fill_quote(p, &i, &j);
		else if (p->str_cmd[i] == '\'')
			fill_single_quote(p, &i, &j);
		else
			fill_no_quote(p, &i, &j, len);
	}
	p->buf[j] = '\0';
}

char			**init_args(int arg_nb, t_parse_cmd p)
{
	char		**args;
	int			i;

	args = malloc(sizeof(char *) * (arg_nb + 2));
	if (!args)
		return (0);
	i = 0;
	while (i < (arg_nb + 2))
	{
		args[i] = NULL;
		i++;
	}
	args[0] = ft_strdup(p.cmd->exe);
	if (!args[0])
	{
		free(args);
		return (0);
	}
	args[arg_nb + 1] = NULL;
	return (args);
}

static void		real_quote_size(t_parse_cmd p, int *size, int *i, int len)
{
	int		to_escape;

	while (*i < len && p.str_cmd[*i] == '"')
	{
		*size = *size + 1;
		*i = *i + 1;
		to_escape = 0;
		while (*i < len && !(p.str_cmd[*i] == '"' && !to_escape))
		{
			if (p.str_cmd[*i] == '\\' && !to_escape)
				to_escape = 1;
			else
				to_escape = 0;
			*size = *size + 1;
			*i = *i + 1;
		}
		*size = *size + 1;
		*i = *i + 1;
	}
}

static void		real_single_quote_size(t_parse_cmd p, int *i, int *size)
{
	*size = *size + 1;
	*i = *i + 1;
	while (p.str_cmd[*i] != '\'')
	{
		*size = *size + 1;
		*i = *i + 1;
	}
	*size = *size + 1;
	*i = *i + 1;
}

int				real_component_size(t_parse_cmd p, int i, int len)
{
	int		size;

	size = 0;
	while (p.str_cmd[i] == '"' || p.str_cmd[i] == '\'' ||
		(i < len && p.str_cmd[i] != ' ' && p.str_cmd[i] != '|'
		&& p.str_cmd[i] != '>' && p.str_cmd[i] != '<'))
	{
		if (p.str_cmd[i] == '"')
			real_quote_size(p, &size, &i, len);
		else if (p.str_cmd[i] == '\'')
			real_single_quote_size(p, &i, &size);
		else
			real_no_quote_size(p, &i, &size, len);
	}
	return (size);
}
