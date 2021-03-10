/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/10 19:06:47 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"
#include <stdio.h>

static int	count_arg(char const *str, int i, int len)
{
	int		count;
	int		to_escape;

	to_escape = 0;
	count = 0;
	while (i < len)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '|' && !to_escape)
			return (count);
		if (i != len)
			count++;
		if (str[i] == '"' && !to_escape)
		{
			i++;
			while (!(str[i] == '"' && !to_escape))
				i++;
			i++;
		}
		else
		{
			while (str[i] != ' ' && i < len && !(str[i] == '|' && !to_escape))
			{
				if (to_escape == 0 && str[i] == '\\')
					to_escape = 1;
				else
					to_escape = 0;
				i++;
			}
		}
		i++;
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

static char	*fill_elem(char *dest, const char *src)
{
	//int		j;

	(void)dest;
	(void)src;
	/*
	j = 0;
	while (src[j] != '\0')
	{
		if ()
		{
			dest[i] = src[j];
			i++;
		}
		j++;
	}
	dest[i] = '\0';
	*/
	return (dest);
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
		size = size_component(p, *i, len);
		printf("size = %d\n", size);
		args[j] = malloc(sizeof(char) * size + 1);
		if (!args[j])
			return (NULL);
		fill_elem(args[j], p.str_cmd);
//		args[j] = trim_d_quote(args[j], size_arg(p.str_cmd, *i, len));
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
	printf("arg_nb = %d\n", arg_nb);
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

int	is_meta_char(char c)
{
	if (c == '>' || c == '<' || c == '*' || c == '?' || c == '['
		|| c == ']' || c == '|' || c == ';' || c == '&' || c == '('
		|| c == ')' || c == '#' || c == '$' || c == '\\' || c == '{'
		|| c == '}' || c == '"' || c == '\'' || c == '`' || c == ';'
		|| c == '=')
		return (1);
	return (0);
}

int	is_meta_char_quote(char c)
{
	if (c == '$' || c == '\\' || c == '"' || c == '`')
		return (1);
	return (0);
}

int	size_var(t_parse_cmd p, int i, int j, int size_name)
{
	int		o;
	int		size_value;

	if (ft_strncmp(p.envp[j], p.str_cmd + i, size_name) == 0)
	{
		if (p.envp[j][size_name] == '=')
		{
			o = 1;
			size_value = 0;
			while (p.envp[j][size_name + o] != '\0')
			{
				size_value++;
				o++;
			}
			return (size_value);
		}
	}
	return (-1);
}

int	dollar_size(t_parse_cmd p, int *size, int *i, int to_escape)
{
	int		size_name;
	int		size_value;
	int		j;

	if (p.str_cmd[*i] == '$' && !to_escape)
	{
		size_name = 0;
		while (ft_isalnum(p.str_cmd[(*i + 1) + size_name]))
			size_name++;
		j = 0;
		while (p.envp[j] != NULL)
		{
			size_value = size_var(p, (*i + 1), j, size_name);
			if (size_value != -1)
			{
				*size = *size + size_value;
				return (size_name);
			}
			j++;
		}
	}
	return (-1);
}

int	size_component(t_parse_cmd p, int i, int len)
{
	int		size;
	int		to_escape;
	int		name_size;

	size = 0;
	to_escape = 0;
	if (p.str_cmd[i] == '"')
	{
		i++;
		while (!(p.str_cmd[i] == '"' && !to_escape))
		{
			if (p.str_cmd[i] == '\\' && !to_escape)
			{
				to_escape = 1;
				size++;
			}
			else
			{
				if (!is_meta_char_quote(p.str_cmd[i]))
					size++;
				name_size = dollar_size(p, &size, &i, to_escape);
				if (name_size != -1)
					i += name_size;
				to_escape = 0;
			}
			i++;
		}
		i++;
	}
	else
	{
		while (p.str_cmd[i] != ' ' && i < len && p.str_cmd[i] != '|')
		{
			i++;
			size++;
		}
	}
	return (size);
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
	*size = size_component(*p, *i, len);

	printf("size = %d\n", *size);

	if (0xCAFE == 0xDECA)
	{
		p->cmd->exe = malloc(sizeof(char) * (*size + 1));
		if (!p->cmd->exe)
			return (0);
		fill_elem(p->cmd->exe, p->str_cmd + *i);
		if (!error)
		{
			free(cmd);
			return (0);
		}
		while (p->str_cmd[*i] == ' ')
			*i = *i + 1;
	}
	return (1);
}

static void	init_parsing(t_parse_cmd *p, char const *str_cmd, char **envp)
{
	p->p_cmd = NULL;
	p->first_cmd = NULL;
	p->str_cmd = str_cmd;
	p->envp = envp;
}

t_cmd	*parse_cmd(char const *str_cmd, int len, char **envp[])
{
	int				i;
	int				size;
	t_parse_cmd		p;

	i = 0;
	init_parsing(&p, str_cmd, *envp);
	while (1)
	{
		if (!init_cmd_exe(&i, &p, len, &size))
			return (NULL);
		if (0xCADE == 5)
		{
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
		exit(0);
	}
	//print_pipe(p.first_cmd);
	return (p.first_cmd);
}
