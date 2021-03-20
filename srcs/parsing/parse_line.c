/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:34:20 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 18:03:02 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

static int			count_cmds(char const *line)
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

static char const	*get_cmd_end(char const *line)
{
	char	is_escaped;

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
	return (line);
}

static int			fill_cmds(t_cmd **cmds, char const *line, char **envp[],
		int last_exit_code)
{
	char const	*backup;
	int			count;

	count = count_cmds(line);
	while (count--)
	{
		backup = line;
		line = get_cmd_end(line);
		*cmds = parse_cmd(backup, line - backup, envp, last_exit_code);
		if (*cmds == NULL)
			return (1);
		line++;
		cmds++;
	}
	*cmds = NULL;
	return (0);
}

t_cmd				**parse_line(char *line, char **envp[], int last_exit_code)
{
	t_cmd	**cmds;

	str_substitute(line, '\t', ' ');
	if (check_line(line))
		return (NULL);
	cmds = malloc((count_cmds(line) + 1) * sizeof(t_cmd *));
	if (cmds == NULL)
		return (NULL);
	if (fill_cmds(cmds, line, envp, last_exit_code))
	{
		free_cmds(cmds);
		return (NULL);
	}
	return (cmds);
}
