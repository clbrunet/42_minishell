/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:42:21 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/20 19:36:35 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	skip_quote(char const *str, int *i)
{
	int		to_escape;

	to_escape = 0;
	*i = *i + 1;
	while (!(str[*i] == '"' && !to_escape))
	{
		if (str[*i] == '\\' && !to_escape)
			to_escape = 1;
		else
			to_escape = 0;
		*i = *i + 1;
	}
	*i = *i + 1;
}

void	skip_single_quote(char const *str, int *i)
{
	*i = *i + 1;
	while (str[*i] != '\'')
		*i = *i + 1;
	*i = *i + 1;
}

void	skip_no_quote(char const *str, int *i, int len)
{
	int		to_escape;

	to_escape = 0;
	while (str[*i] != ' ' && !(str[*i] == '"' && !to_escape) &&
			!(str[*i] == '\'' && !to_escape) &&
			!(str[*i] == '|' && !to_escape) && *i < len)
	{
		if (str[*i] == '\\' && !to_escape)
			to_escape = 1;
		else
			to_escape = 0;
		*i = *i + 1;
	}
}

void	skip_redirection(char const *str, int *i, int len)
{
	*i = *i + 1;
	if ((str[*i] == '>' || str[*i] == '<') && *i < len)
		*i = *i + 1;
	while (1)
	{
		while (str[*i] == ' ')
			*i = *i + 1;
		skip_strings(str, i, len);
		while (str[*i] == ' ')
			*i = *i + 1;
		if ((str[*i] == '<' || str[*i] == '>') && *i < len)
		{
			*i = *i + 1;
			if ((str[*i] == '>' || str[*i] == '<') && *i < len)
				*i = *i + 1;
		}
		else
			break ;
	}
}
