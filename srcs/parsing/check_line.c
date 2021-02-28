/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:19:22 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 11:36:11 by clbrunet         ###   ########.fr       */
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

/* static	int	check_brackets(char const *command) */
/* { */
/* 	char	is_escaped; */

/* 	is_escaped = 0; */
/* 	while (*command && !(*command == ';' && !is_escaped)) */
/* 	{ */
/* 		if ((*command == '\'' || *command == '"') && !is_escaped) */
/* 			command = trim_inner_quotes(command, *command); */
/* 		else if (*command == '(' && !is_escaped) */
/* 		{ */
/* 			command = trim_inner_brackets(command); */
/* 			if (command == NULL) */
/* 				return (syntax_error("newline")); */
/* 		} */
/* 		else if (*command == ')' && !is_escaped) */
/* 			return (syntax_error(")")); */
/* 		else if (*command == '\\') */
/* 			is_escaped = !is_escaped; */
/* 		else */
/* 			is_escaped = 0; */
/* 		command++; */
/* 	} */
/* 	return (0); */
/* } */

/* static int	check_ending(char const *command) */
/* { */
/* 	char const	*backup; */

/* 	backup = command; */
/* 	command += ft_strlen(command) - 1; */
/* 	while (backup <= command) */
/* 	{ */
/* 		/1* if (*command == '|') *1/ */
/* 	} */
/* 	return (0); */
/* } */

int	check_line(char const *line)
{
	return (check_quotes(line) || check_semicolons(line));
}
