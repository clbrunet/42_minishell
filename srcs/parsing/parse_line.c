/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:34:20 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 14:39:51 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

static int	count_commands(char const *line)
{
	int		count;
	char	is_new_command;
	char	is_escaped;

	is_escaped = 0;
	is_new_command = 1;
	count = 0;
	while (*line)
	{
		if (*line != ' ' && is_new_command)
		{
			count++;
			is_new_command = 0;
		}
		if (ft_strchr("'\"", *line) && !is_escaped)
			line = trim_inner_quotes(line, *line);
		else if (*line == ';' && !is_escaped)
			is_new_command = 1;
		else if (*line == '\\')
			is_escaped = !is_escaped;
		else
			is_escaped = 0;
		line++;
	}
	return (count);
}

static int	fill_commands(char **commands, char const *line, int count)
{
	char const	*backup;
	char		is_escaped;

	while (count--)
	{
		backup = line;
		is_escaped = 0;
		while (*line && !(*line == ';' && !is_escaped))
		{
			if (ft_strchr("'\"", *line) && !is_escaped)
				line = trim_inner_quotes(line, *line);
			else if (*line == '\\')
				is_escaped = !is_escaped;
			else
				is_escaped = 0;
			line++;
		}
		*commands = ft_strndup(backup, line - backup);
		if (*commands == NULL)
			return (1);
		line++;
		commands++;
	}
	*commands = NULL;
	return (0);
}

char	**parse_line(char *line)
{
	char	**commands;
	int		count;

	str_substitute(line, '\t', ' ');
	if (check_line(line))
		return (NULL);
	count = count_commands(line);
	commands = malloc((count + 1) * sizeof(char *));
	if (commands == NULL)
		return (NULL);
	if (fill_commands(commands, line, count))
	{
		free_strs(commands);
		return (NULL);
	}
	return (commands);
}
