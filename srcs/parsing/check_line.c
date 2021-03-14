/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:19:22 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/14 13:10:36 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

static	int	check_quotes(char const *line)
{
	char	is_escaped;

	is_escaped = 0;
	while (*line)
	{
		if (ft_strchr("'\"", *line) && !is_escaped)
		{
			line = trim_inner_quotes(line, *line);
			if (line == NULL)
				return (syntax_error("newline"));
		}
		else if (*line == '\\')
			is_escaped = !is_escaped;
		else
			is_escaped = 0;
		line++;
	}
	return (0);
}

static	int	check_semicolons(char const *line)
{
	char	last_nonspace_char;
	char	is_escaped;

	is_escaped = 0;
	last_nonspace_char = ';';
	while (*line)
	{
		if (ft_strchr("'\"", *line) && !is_escaped)
			line = trim_inner_quotes(line, *line);
		else if (*line == ';' && !is_escaped)
		{
			if (*(line + 1) == ';')
				return (syntax_error(";;"));
			else if (last_nonspace_char == ';')
				return (syntax_error(";"));
		}
		else if (*line == '\\')
			is_escaped = !is_escaped;
		else
			is_escaped = 0;
		if (*line != ' ')
			last_nonspace_char = *line;
		line++;
	}
	return (0);
}

static int	check_cmds_ending_tests(char const **line, char *is_escaped,
		char *is_smth_expected)
{
	char	unexpected_token[2];

	unexpected_token[1] = '\0';
	if (ft_strchr("'\"", **line) && !*is_escaped)
		*line = trim_inner_quotes(*line, **line);
	else if (ft_strchr("<>|", **line) && !*is_escaped && *is_smth_expected)
	{
		unexpected_token[0] = **line;
		return (syntax_error(unexpected_token));
	}
	else if (ft_strchr("<>|", **line) && !*is_escaped)
		*is_smth_expected = 1;
	else if (**line == ';' && !*is_escaped && *is_smth_expected)
		return (syntax_error(";"));
	else if (**line == '\\')
		*is_escaped = !*is_escaped;
	else
		*is_escaped = 0;
	if (!ft_strchr("<>| ", **line))
		*is_smth_expected = 0;
	return (0);
}

static int	check_cmds_ending(char const *line)
{
	char	is_escaped;
	char	is_smth_expected;

	is_escaped = 0;
	is_smth_expected = 0;
	while (*line)
	{
		if (check_cmds_ending_tests(&line, &is_escaped, &is_smth_expected))
			return (1);
		line++;
	}
	if (is_smth_expected)
		return (syntax_error("newline"));
	return (0);
}

int	check_line(char const *line)
{
	return (check_quotes(line) || check_semicolons(line)
		|| check_cmds_ending(line));
}
