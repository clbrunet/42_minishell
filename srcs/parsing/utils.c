/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:20:56 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 13:25:52 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

char const	*trim_inner_quotes(char const *line, char quote)
{
	char	is_escaped;

	is_escaped = 0;
	line++;
	while (*line)
	{
		if (*line == quote && !is_escaped)
			return (line);
		else if (*line == '\\')
			is_escaped = !is_escaped;
		else
			is_escaped = 0;
		line++;
	}
	return (NULL);
}

char const	*trim_inner_brackets(char const *line)
{
	char	is_escaped;

	is_escaped = 0;
	line++;
	while (*line)
	{
		if (ft_strchr("'\"", *line) && !is_escaped)
			line = trim_inner_quotes(line, *line);
		else if (*line == '(' && !is_escaped)
		{
			line = trim_inner_brackets(line);
			if (line == NULL)
				return (NULL);
		}
		else if (*line == ')' && !is_escaped)
			return (line);
		else if (*line == '\\')
			is_escaped = !is_escaped;
		else
			is_escaped = 0;
		line++;
	}
	return (NULL);
}
