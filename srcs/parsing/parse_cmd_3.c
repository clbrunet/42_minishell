/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:12:35 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/17 16:13:20 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

int				count_arg(char const *str, int i, int len)
{
	int		count;
	int		to_escape;

	to_escape = 0;
	count = 0;
	while (i < len)
	{
		while (str[i] == ' ')
			i++;
		if ((str[i] == '>' || str[i] == '<'))
			skip_redirection(str, &i, len);
		if (str[i] == '|' && !to_escape)
			return (count);
		if (i != len)
			count++;
		if (str[i] == '"' && !to_escape)
			skip_quote(str, &i);
		else if (str[i] == '\'' && !to_escape)
			skip_single_quote(str, &i);
		else
			skip_no_quote(str, &i, len);
	}
	return (count);
}

int				size_var(t_parse_cmd p, int i, int j, int size_name)
{
	int		o;
	int		size_value;

	if (ft_strncmp(p.envp[j], p.str_cmd + i, size_name) == 0)
	{
		if (p.envp[j][size_name] == '=')
		{
			o = 1;
			size_value = 0;
			while (p.envp[j][size_name + o] != '\0')
			{
				size_value++;
				o++;
			}
			return (size_value);
		}
	}
	return (-1);
}

static void		cpy_var_value(t_parse_cmd *p, int size_name, int k, int *j)
{
	int		size_var;
	int		o;

	size_var = 0;
	while (p->envp[k][size_name + 1 + size_var] != '\0')
		size_var++;
	o = 0;
	while (p->envp[k][size_name + o + 1] != '\0')
	{
		p->buf[o + *j] = p->envp[k][size_name + o + 1];
		o++;
	}
	p->buf[o + *j] = '\0';
	*j = *j + size_var;
}

static int		cpy_var(t_parse_cmd *p, int i, int *j, int size_name)
{
	int		k;

	k = 0;
	while (p->envp[k] != NULL)
	{
		if (ft_strncmp(p->envp[k], p->str_cmd + i + 1, size_name) == 0)
		{
			if (p->envp[k][size_name] == '=')
				cpy_var_value(p, size_name, k, j);
			return (1);
		}
		k++;
	}
	return (-1);
}

int				fill_dollar(t_parse_cmd *p, int i, int *j, int to_escape)
{
	int		size_name;
	int		error;

	size_name = 0;
	if (p->str_cmd[i] == '$' && !to_escape && !ft_isalpha(p->str_cmd[i + 1])
		&& p->str_cmd[i] != '_')
	{
		p->buf[*j] = '$';
		p->buf[*j + 1] = '\0';
		*j = *j + 1;
	}
	else if (p->str_cmd[i] == '$' && !to_escape)
	{
		while (ft_isalnum(p->str_cmd[(i + 1) + size_name]))
			size_name++;
		error = cpy_var(p, i, j, size_name);
		if (error != -1)
			return (size_name);
	}
	return (size_name);
}
