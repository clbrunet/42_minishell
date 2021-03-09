/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/09 09:58:57 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"


static int	count_arg(char const *str, int i, int len)
{
	int		count;

	count = 0;
	while (i < len)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '|')
			return (count);
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

	if (!arg)
		return (NULL);
	if ((arg[0] == '"' && arg[size - 1] == '"')
		|| (arg[0] == '\'' && arg[size - 1] == '\''))
	{
		arg_trimmed = malloc(sizeof(char) * (size - 1));
		if (!arg_trimmed)
			return (NULL);
		ft_strncpy(arg_trimmed, arg + 1, size - 2);
		free(arg);
		return (arg_trimmed);
	}
	else
		return (arg);
}

static char	*strncpy_arg(char *dest, const char *src, int n)
{
	int		i;
	int		j;

	if (!dest)
		return (NULL);
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

int	size_arg(const char *str, int i, int len)
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

static char	**init_args(int	arg_nb, t_parse_cmd p)
{
	char		**args;
	int			i;

	args = malloc(sizeof(char *) * (arg_nb + 2));
	if (!args)
		return (0);
	i = 0;
	while (i < (arg_nb + 2))
	{
		args[i] = NULL;
		i++;
	}
	args[0] = ft_strdup(p.cmd->exe);
	if (!args[0])
	{
		free(args);
		return (0);
	}
	args[arg_nb + 1] = NULL;
	return (args);
}

static char	**fill_args(t_parse_cmd p, int *i, int len, int arg_nb)
{
	char		**args;
	int			size;
	int			j;

	args = init_args(arg_nb, p);
	if (!args)
		return (0);
	j = 1;
	while (*i < len)
	{
		while (p.str_cmd[*i] == ' ')
			*i = *i + 1;
		if (p.str_cmd[*i] == '|' || p.str_cmd[*i] == '\0' || *i >= len)
			return (args);
		size = size_component(p.str_cmd, *i, len);
		args[j] = malloc(sizeof(char) * (size_arg(p.str_cmd, *i, len) + 1));
		strncpy_arg(args[j], p.str_cmd + *i, size);
		args[j] = trim_d_quote(args[j], size_arg(p.str_cmd, *i, len));
		if (!args[j])
			return (NULL);
		*i = *i + size;
		j++;
	}
	return (args);
}

static int	set_previous_pipe(t_parse_cmd *p, int *i)
{
	if (p->p_cmd)
		p->p_cmd->pipe = p->cmd;
	else
	{
		if (p->str_cmd[*i] != '|')
			return (0);
	}
	p->p_cmd = p->cmd;
	*i = *i + 1;
	return (1);
}

static char	**parse_arguments(int *i, int size, int len, t_parse_cmd p)
{
	int		arg_nb;
	char	**args;

	*i = *i + size;
	arg_nb = count_arg(p.str_cmd, *i, len);
	args = fill_args(p, i, len, arg_nb);
	if (!args)
		return (NULL);
	return (args);
}


/*
static void	print_pipe(t_cmd *p)
{
	int	i;

	while (p != NULL)
	{
		printf("cmd = %p\n", p);
		printf("exe = %s\n", p->exe);
		i = 0;
		while (p->args[i] != NULL)
		{
			printf("arg #%d: %s\n", i, p->args[i]);
			i++;
		}
		p = p->pipe;
	}
}
*/

t_cmd	*free_cmd_and_content(t_cmd *cmd)
{
	free_cmd_content(cmd, cmd);
	free_cmd(cmd);
	return (NULL);
}

static int	size_component(char const *str_cmd, int i, int len)
{
	int		size;

	size = 0;
	if (str_cmd[i] == '"')
	{
		i++;
		size++;
		while (str_cmd[i] != '"' || (str_cmd[i] == '"'
				&& str_cmd[i - 1] == '\\'))
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

static int	fill_exe(t_parse_cmd *p, int i, int size)
{
	int		j;

	p->cmd->exe = malloc(sizeof(char) * (size + 1));
	if (!p->cmd->exe)
		return (0);
	j = 0;
	while (j < size)
	{
		p->cmd->exe[j] = p->str_cmd[i];
		i++;
		j++;
	}
	p->cmd->exe[j] = '\0';
	return (1);
}
static int	init_cmd_exe(int *i, t_parse_cmd *p, int len, int *size)
{
	t_cmd	*cmd;
	int		error;

	cmd = malloc(sizeof(t_cmd) * (1));
	if (!cmd)
	{
		p->cmd = 0;
		return (0);
	}
	if (*i == 0)
		p->first_cmd = cmd;
	while (p->str_cmd[*i] == ' ')
		*i = *i + 1;
	p->cmd = cmd;
	p->cmd->exe = NULL;
	p->cmd->args = NULL;
	p->cmd->pipe = NULL;
	*size = size_component(p->str_cmd, *i, len);
	error = fill_exe(p, *i, *size);
	if (!error)
	{
		free(cmd);
		return (0);
	}
	while (p->str_cmd[*i] == ' ')
		*i = *i + 1;
	return (1);
}

static void	init_parsing(t_parse_cmd *p, char const *str_cmd)
{
	p->p_cmd = NULL;
	p->first_cmd = NULL;
	p->str_cmd = str_cmd;
}

t_cmd	*parse_cmd(char const *str_cmd, int len)
{
	int				i;
	int				size;
	t_parse_cmd		p;

	i = 0;
	init_parsing(&p, str_cmd);
	while (1)
	{
		if (!init_cmd_exe(&i, &p, len, &size))
			return (NULL);
		p.cmd->args = parse_arguments(&i, size, len, p);
		if (!p.cmd->args)
		{
			free_cmd_content(p.first_cmd, p.first_cmd);
			free_cmd(p.first_cmd);
			return (NULL);
		}
		if (!set_previous_pipe(&p, &i) || i > len)
			break ;
	}
	//print_pipe(p.first_cmd);
	return (p.first_cmd);
}
