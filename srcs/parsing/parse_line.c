/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:34:20 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/23 14:40:02 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

static char const	*trim_in_quote(char const *line, char quote)
{
	int		backslash_count;

	backslash_count = 0;
	line++;
	while (*line)
	{
		if (*line == '\\')
			backslash_count++;
		else
			backslash_count = 0;
		line++;
		if (*line == quote && backslash_count % 2 == 0)
			return (line);
	}
	return (NULL);
}

static int	check_line(char const *line)
{
	char	last_nonspace_char;

	last_nonspace_char = ';';
	while (*line)
	{
		if (*line == '\'' || *line == '"')
		{
			line = trim_in_quote(line, *line);
			if (line == NULL)
				return (syntax_error("newline"));
		}
		else if (*line == ';')
		{
			if (*(line + 1) == ';')
				return (syntax_error(";;"));
			else if (last_nonspace_char == ';')
				return (syntax_error(";"));
		}
		if (*line != ' ')
			last_nonspace_char = *line;
		line++;
	}
	return (0);
}

static int	count_commands(char const *line)
{
	int		count;
	int		new_command;

	count = 0;
	new_command = 1;
	while (*line)
	{
		if (*line == '\'' || *line == '"')
			line = trim_in_quote(line, *line);
		if (*line == ';')
			new_command = 1;
		else if (*line != ' ' && new_command)
		{
			count++;
			new_command = 0;
		}
		line++;
	}
	return (count);
}

static int	fill_commands(char **commands, char const *line, int count)
{
	int			command_index;
	char const	*backup;

	command_index = 0;
	while (command_index < count)
	{
		backup = line;
		while (*line && *line != ';')
		{
			if (*line == '\'' || *line == '"')
				line = trim_in_quote(line, *line);
			line++;
		}
		commands[command_index] = ft_strndup(backup, line - backup);
		if (commands[command_index] == NULL)
			return (1);
		line++;
		command_index++;
	}
	commands[command_index] = NULL;
	return (0);
}

char	**parse_line(char const *line)
{
	char	**commands;
	int		count;

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
