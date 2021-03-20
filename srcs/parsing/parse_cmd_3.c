/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:12:35 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/20 18:30:53 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

#include <stdio.h>
int				exist_if_dollar(char const *str, int i, char **envp, int len)
{
	int	j;
	int	size_name;

	if (str[i] == '$')
	{
		i++;
		size_name = 0;
		while (ft_isalnum(str[i]) || str[i] == '_')
		{
			size_name++;
			i++;
		}
		i -= size_name;
		j = 0;
		while (envp[j] != NULL)
		{
			if (ft_strncmp(envp[j], &str[i], size_name) == 0)
			{
				if (envp[j][size_name] == '=')
					return (1);
			}
			j++;
		}
		if ((i + size_name) >= len || str[i + size_name] == ' ' || str[i + size_name] == '<'
				|| str[i + size_name] == '>' || str[i + size_name] == '|')
			return (0);
		return (1);
	}
	return (1);
}
int				count_arg(char const *str, int i, int len, char **envp)
{
	int		count;

	count = 0;
	while (i < len)
	{
		while (str[i] == ' ')
			i++;
		if ((str[i] == '>' || str[i] == '<'))
			skip_redirection(str, &i, len);
		if (str[i] == '|')
			return (count);
		printf("exist = %d\n", exist_if_dollar(str, i, envp,len));
		if (i != len && exist_if_dollar(str, i, envp, len))
			count++;
		skip_strings(str, &i, len);
	}
	printf("count = %d", count);
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

void				fill_last_exit_code(int last_exit_code, char *buf, int *j)
{
	if (last_exit_code >= 10)
		fill_last_exit_code(last_exit_code / 10, buf, j);
	buf[*j] = ((last_exit_code % 10) + 48);
	*j = *j + 1;
}

int				fill_dollar(t_parse_cmd *p, int i, int *j, int to_escape)
{
	int		size_name;
	int		error;

	size_name = 0;
	if (p->str_cmd[i] == '$' && !to_escape && p->str_cmd[i + 1] == '?')
	{
		fill_last_exit_code(p->last_exit_code, p->buf, j);
		p->buf[*j] = '\0';
		return (1);
	}
	else if (p->str_cmd[i] == '$' && !to_escape && !ft_isalpha(p->str_cmd[i + 1])
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
