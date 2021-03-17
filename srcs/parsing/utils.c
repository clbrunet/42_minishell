/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:20:56 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 08:34:50 by clbrunet         ###   ########.fr       */
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

char		*str_substitute(char *str, char old, char new)
{
	char	*backup;

	backup = str;
	while (*str)
	{
		if (*str == old)
			*str = new;
		str++;
	}
	return (backup);
}
