/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/03 15:10:11 by mlebrun          ###   ########.fr       */
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

static int fill_exe(char *elem, char const *str_cmd, int i, int size)
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
	return (1);
}

static int	count_arg(char const *str_cmd, int i, int len)
{
	int		count;

	count = 0;
	while (i < len)
	{
		while (str_cmd[i] == ' ')
			i++;
		if (str_cmd[i] == '|')
			return (count);
		if (i != len)
			count++;
		if (str_cmd[i] == '"')
		{
			i++;
			while (str_cmd[i] != '"' || (str_cmd[i] == '"' &&
				str_cmd[i - 1] == '\\'))
				i++;
			i++;
		}
		else
		{
			while (str_cmd[i] != ' ' && i < len)
				i++;
		}
	}
	return (count);
}

char	*trim_d_quote(char *arg, int size)
{
	char	*arg_trimmed;

	if ((arg[0] == '"' && arg[size - 1] == '"') || (arg[0] == '\'' && arg[size - 1] == '\''))
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

int		size_arg(const char *str_cmd, int i, int len)
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
			if (!(str_cmd[i] == '"' && str_cmd[i - 1] == '\\'))
				size++;
			i++;
		}
		i++;
		size++;
	}
	else
	{
		while (str_cmd[i] != ' ' && i < len)
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
		if (str_cmd[*i] == '|')
			return (args);
		if (str_cmd[*i] == '\0')
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

static void	set_previous_pipe(t_cmd *cmd, t_cmd *p_cmd)
{
	if (!p_cmd)
	{
		cmd->pipe = NULL;
		return ;
	}
	p_cmd->pipe = cmd;
}


t_cmd	*parse_cmd(char const *str_cmd, int len)
{
	t_cmd	*cmd;
	t_cmd	*p_cmd;
	int		i;
	int		size;
	int		arg_nb;
	t_cmd	*first_cmd;

	if (check_cmd(str_cmd, len))
		return (NULL);
	i = 0;
	p_cmd = NULL;
	while (1)
	{
		cmd = malloc(sizeof(t_cmd) * (1));
		if (!cmd)
			return (NULL);
		if (i == 0)
			first_cmd = cmd;
		while (str_cmd[i] == ' ')
			i++;
		size = size_component(str_cmd, i, len);
//		printf("size = %d\n", size);
		cmd->exe = malloc(sizeof(char) * (size + 1));
		fill_exe(cmd->exe, str_cmd, i, size);
		if (str_cmd[i + size] == '|')
		{
			i += size + 1;
			if (i > len)
				break ;
			set_previous_pipe(cmd, p_cmd);
			cmd->args = NULL;
			p_cmd = cmd;
			printf("result:\n");
			printf("exe = %s\n", cmd->exe);
			int j;
			j = 0;
			while (cmd->args && cmd->args[j] != 0)
			{
				printf("a: %s\n", cmd->args[j]);
				j++;
			}
		}
		else
		{
			i += size + 1;
			arg_nb = count_arg(str_cmd, i, len);
			cmd->args = fill_args(str_cmd, &i, len, arg_nb);
			printf("result:\n");
			printf("exe = %s\n", cmd->exe);
			int j;
			j = 0;
			while (cmd->args[j] != 0)
			{
				printf("a: %s\n", cmd->args[j]);
				j++;
			}
			if (i > len)
				break ;
			set_previous_pipe(cmd, p_cmd);
			if (str_cmd[i] != '|')
				break ;
			p_cmd = cmd;
			i++;
		}
	}
	return (cmd);
}
