/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:16:12 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/20 21:42:39 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "parsing.h"

static int		dollar_exist(char **envp, char const *str, int i,
				int size_name)
{
	int		j;

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
	return (0);
}

int				exist_if_dollar(char const *str, int i, char **envp, int len)
{
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
		if (dollar_exist(envp, str, i, size_name))
			return (1);
		if ((i + size_name) >= len || str[i + size_name] == ' ' ||
			str[i + size_name] == '<' || str[i + size_name] == '>' ||
			str[i + size_name] == '|')
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
		if (i != len && exist_if_dollar(str, i, envp, len))
			count++;
		skip_strings(str, &i, len);
	}
	return (count);
}

void			fill_one_dollar(t_parse_cmd *p, int *j)
{
	p->buf[*j] = '$';
	p->buf[*j + 1] = '\0';
	*j = *j + 1;
}

char			*fill_buf_with_arg(t_parse_cmd *p, int *i, int len)
{
	int			size;

	size = size_component_formated(*p, *i, len);
	p->buf = malloc(sizeof(char) * size + 1);
	if (!p->buf)
		return (NULL);
	fill_buf(p, len, *i);
	return (p->buf);
}
