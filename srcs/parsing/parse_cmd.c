/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/04 15:21:47 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"
#include <stdio.h>

static int	size_component(char const *str_cmd, int i, int len)
{
	int		size;

	size = 0;
	if (str_cmd[i] == '"')
	{
		i++;
		size++;
		while (str_cmd[i] != '"' || (str_cmd[i] == '"' &&
			str_cmd[i - 1] == '\\'))
		{
			i++;
			size++;
		}
		i++;
		size++;
	}
	else
	{
		while (str_cmd[i] != ' ' && i < len && str_cmd[i] != '|')
		{
			i++;
			size++;
		}
	}
	return (size);
}

static void fill_exe(char *elem, char const *str_cmd, int i, int size)
{
	int		j;

	j = 0;
	while (j < size)
	{
		elem[j] = str_cmd[i];
		i++;
		j++;
	}
	elem[j] = '\0';
}

static int	count_arg(char const *str, int i, int len)
{
	int		count;

	count = 0;
	while (i < len)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '|')
		{
			return (count);
		}
		if (i != len)
			count++;
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' || (str[i] == '"' && str[i - 1] == '\\'))
				i++;
			i++;
		}
		else
		{
			while (str[i] != ' ' && i < len && str[i] != '|')
				i++;
		}
	}
	return (count);
}

char	*trim_d_quote(char *arg, int size)
{
	char	*arg_trimmed;

	if ((arg[0] == '"' && arg[size - 1] == '"')
		|| (arg[0] == '\'' && arg[size - 1] == '\''))
	{
		arg_trimmed = malloc(sizeof(char) * (size - 1));
		ft_strncpy(arg_trimmed, arg + 1, size - 2);
		return (arg_trimmed);
	}
	else
		return (arg);
}

static char		*strncpy_arg(char *dest, const char *src, int n)
{
	int		i;
	int		j;

	(void)n;
	i = 0;
	j = 0;
	while (src[j] != '\0' && j < n)
	{
		if (!((src[j] == '\\' && src[j + 1] == '"')))
		{
			dest[i] = src[j];
			i++;
		}
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int		size_arg(const char *str, int i, int len)
{
	int		size;

	size = 0;
	if (str[i] == '"')
	{
		i++;
		size++;
		while (str[i] != '"' || (str[i] == '"' && str[i - 1] == '\\'))
		{
			if (!(str[i] == '"' && str[i - 1] == '\\'))
				size++;
			i++;
		}
		i++;
		size++;
	}
	else
	{
		while (str[i] != ' ' && i < len)
		{
			i++;
			size++;
		}
	}
	return (size);
}

static char	**fill_args(const char *str_cmd, int *i, int len, int arg_nb)
{
	char	**args;
	int		size;
	int		j;

	args = malloc(sizeof(char *) * (arg_nb + 1));
	args[arg_nb] = NULL;
	if (!args)
		return (0);
	j = 0;
	while (*i < len)
	{
		while (str_cmd[*i] == ' ')
			*i = *i + 1;
		if (str_cmd[*i] == '|' || str_cmd[*i] == '\0')
			return (args);
		size = size_component(str_cmd, *i, len);
		args[j] = malloc(sizeof(char) * (size_arg(str_cmd, *i, len) + 1));
		strncpy_arg(args[j], str_cmd + *i, size);
		args[j] = trim_d_quote(args[j], size_arg(str_cmd, *i, len));
		*i = *i + size;
		j++;
	}
	return (args);
}

static int	set_previous_pipe(t_cmd *cmd, t_cmd *p_cmd, const char *str_cmd,
			int *i)
{
	if (!p_cmd)
		cmd->pipe = NULL;
	else
		p_cmd->pipe = cmd;
	if (str_cmd[*i] != '|')
		return (0);
	p_cmd = cmd;
	*i = *i + 1;
	return (1);
}

char	**parse_arguments(int *i, int size, int len, const char *str_cmd)
{
	int		arg_nb;
	char	**args;

	*i = *i + (size + 1);
	arg_nb = count_arg(str_cmd, *i, len);
	args = fill_args(str_cmd, i, len, arg_nb);
	if (!args)
		return (NULL);
	return (args);
}

t_cmd	*init_cmd(int *i, t_cmd *first_cmd, char const *str_cmd)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * (1));
	if (!cmd)
		return (NULL);
	if (*i == 0)
		first_cmd = cmd;
	while (str_cmd[*i] == ' ')
		*i = *i + 1;
	return (cmd);
}

int		pipe_no_arg(int i, int len, t_cmd *cmd, t_cmd *p_cmd)
{
	if (i > len)
		return (0);
	if (!p_cmd)
	{
		cmd->pipe = NULL;
		return (1);
	}
	p_cmd->pipe = cmd;
	cmd->args = NULL;
	p_cmd = cmd;
	return (1);
}

t_cmd	*parse_cmd(char const *str_cmd, int len)
{
	//t_cmd	*cmd;
//	t_cmd	*p_cmd;
	int		i;
	int		size;
	//t_cmd	*first_cmd;
	t_parse_cmd		p;

	

	i = 0;
	p.p_cmd = NULL;
	p.first_cmd = NULL;
	while (1)
	{
		cmd = init_cmd(&i, first_cmd, str_cmd);
		if (!cmd)
			return (NULL);
		size = size_component(str_cmd, i, len);
		cmd->exe = malloc(sizeof(char) * (size + 1));
		fill_exe(cmd->exe, str_cmd, i, size);
		if (str_cmd[i + size] == '|')
		{
			i += size + 1;
			if (!pipe_no_arg(i, len, cmd, p_cmd))
				break ;
		}
		else
		{
			cmd->args = parse_arguments(&i, size, len, str_cmd);
			if (!cmd->args)
				return (NULL);
			if (i > len || !set_previous_pipe(cmd, p_cmd, str_cmd, &i))
				break ;
		}
	}
	return (cmd);
}
			/*
			printf("exe = %s\n", cmd->exe);
			int j;
			j = 0;
			while (cmd->args[j] != NULL)
			{
				printf("a: %s\n", cmd->args[j]);
				fflush(stdout);
				j++;
			}
			*/
