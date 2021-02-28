/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:34:20 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/28 18:31:30 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

static int	count_cmds(char const *line)
{
	int		count;
	char	is_new_cmd;
	char	is_escaped;

	is_escaped = 0;
	is_new_cmd = 1;
	count = 0;
	while (*line)
	{
		if (*line != ' ' && is_new_cmd)
		{
			count++;
			is_new_cmd = 0;
		}
		if (ft_strchr("'\"", *line) && !is_escaped)
			line = trim_inner_quotes(line, *line);
		else if (*line == ';' && !is_escaped)
			is_new_cmd = 1;
		else if (*line == '\\')
			is_escaped = !is_escaped;
		else
			is_escaped = 0;
		line++;
	}
	return (count);
}

static int	fill_cmds(t_cmd **cmds, char const *line, int count)
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
		*cmds = parse_cmd(backup, line - backup);
		if (*cmds == NULL)
			return (1);
		line++;
		cmds++;
	}
	*cmds = NULL;
	return (0);
}

t_cmd	**parse_line(char *line)
{
	t_cmd	**cmds;
	int		count;

	str_substitute(line, '\t', ' ');
	if (check_line(line))
		return (NULL);
	count = count_cmds(line);
	cmds = malloc((count + 1) * sizeof(t_cmd *));
	if (cmds == NULL)
		return (NULL);
	if (fill_cmds(cmds, line, count))
	{
		free_cmds(cmds);
		return (NULL);
	}
	return (cmds);
}
