/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:12:58 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/20 21:29:24 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "parsing.h"

static int		search_var(t_parse_cmd p, int *i, int size_name, int *size)
{
	int		j;
	int		size_value;

	j = 0;
	while (p.envp[j] != NULL)
	{
		size_value = size_var(p, (*i + 1), j, size_name);
		if (size_value != -1)
		{
			*size = *size + size_value;
			return (size_name);
		}
		j++;
	}
	return (size_name);
}

int				dollar_size(t_parse_cmd p, int *size, int *i, int to_escape)
{
	int		size_name;

	size_name = 0;
	if (p.str_cmd[*i] == '$' && !to_escape && p.str_cmd[*i + 1] == '?')
	{
		*size = *size + ft_size_nb(p.last_exit_code);
		return (1);
	}
	else if (p.str_cmd[*i] == '$' && !to_escape
		&& !ft_isalpha(p.str_cmd[*i + 1]) && p.str_cmd[*i] != '_')
	{
		*size = *size + 1;
		return (0);
	}
	else if (p.str_cmd[*i] == '$' && !to_escape)
	{
		while (ft_isalnum(p.str_cmd[(*i + 1) + size_name]))
			size_name++;
		size_name = search_var(p, i, size_name, size);
		return (size_name);
	}
	return (0);
}

void			size_quote(t_parse_cmd p, int *i, int *size)
{
	int		to_escape;
	int		name_size;

	to_escape = 0;
	*i = *i + 1;
	while (!(p.str_cmd[*i] == '"' && !to_escape))
	{
		if (p.str_cmd[*i] == '\\' && !to_escape)
		{
			to_escape = 1;
			*size = *size + 1;
		}
		else
		{
			if (!is_meta_char_quote(p.str_cmd[*i]))
				*size = *size + 1;
			name_size = dollar_size(p, size, i, to_escape);
			*i = *i + name_size;
			to_escape = 0;
		}
		*i = *i + 1;
	}
	*i = *i + 1;
}

static void		size_no_quote(t_parse_cmd p, int *i, int *size, int len)
{
	int		to_escape;
	int		name_size;

	to_escape = 0;
	while (*i < len && p.str_cmd[*i] != ' ' &&
			!(p.str_cmd[*i] == '>' && !to_escape) &&
			!(p.str_cmd[*i] == '<' && !to_escape) &&
			!(p.str_cmd[*i] == '|' && !to_escape) &&
			!(p.str_cmd[*i] == '"' && !to_escape))
	{
		if (p.str_cmd[*i] == '\\' && !to_escape)
		{
			to_escape = 1;
			*size = *size + 1;
		}
		else
		{
			if (!is_meta_char(p.str_cmd[*i]))
				*size = *size + 1;
			name_size = dollar_size(p, size, i, to_escape);
			*i = *i + name_size;
			to_escape = 0;
		}
		*i = *i + 1;
	}
}

int				size_component_formated(t_parse_cmd p, int i, int len)
{
	int		size;

	size = 0;
	while (p.str_cmd[i] == '"' || p.str_cmd[i] == '\''
			|| (p.str_cmd[i] != ' ' && p.str_cmd[i] != '|'
			&& p.str_cmd[i] != '<' && p.str_cmd[i] != '>' && i < len))
	{
		if (p.str_cmd[i] == '"')
			size_quote(p, &i, &size);
		else if (p.str_cmd[i] == '\'')
		{
			i++;
			while (p.str_cmd[i] != '\'')
			{
				i++;
				size++;
			}
			i++;
		}
		else
			size_no_quote(p, &i, &size, len);
	}
	return (size);
}
