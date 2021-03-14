/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/12 11:45:21 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"
#include <stdio.h>

static void	skip_redirection(char const *str, int *i, int len)
{
	int	to_escape;

	*i = *i + 1;
	if ((str[*i] == '>' || str[*i] == '<') && *i < len)
		*i = *i + 1;
	while (1)
	{
		while (str[*i] == ' ')
			*i = *i + 1;
		to_escape = 0;
		if (str[*i] == '"')
		{
			*i = *i + 1;
			while (str[*i] != '"' && !to_escape)
			{
				if (str[*i] == '\\' && !to_escape)
					to_escape = 1;
				else
					to_escape = 0;
			}
		}
		else if (str[*i] == '\'')
		{
			*i = *i + 1;
			while (str[*i] != '\'')
				*i = *i + 1;
		}
		else
		{
			while ((str[*i] != ' ' && str[*i] != '|') && *i < len)
				*i = *i + 1;
		}

		while (str[*i] == ' ')
			*i = *i + 1;
		if ((str[*i] == '<' || str[*i] == '>') && *i < len)
		{
			*i = *i + 1;
			if ((str[*i] == '>' || str[*i] == '<') && *i < len)
				*i = *i + 1;
		}
		else
			break ;
	}
}

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
		if ((str[i] == '>' || str[i] == '<'))
			skip_redirection(str, &i, len);
		if (str[i] == '|' && !to_escape)
			return (count);
		if (i != len)
			count++;
		if (str[i] == '"' && !to_escape)
		{
			i++;
			while (!(str[i] == '"' && !to_escape))
			{
				if (str[i] == '\\' && !to_escape)
					to_escape = 1;
				else
					to_escape = 0;
				i++;
			}
			i++;
		}
		else if (str[i] == '\'' && !to_escape)
		{
			i++;
			while (str[i] != '\'')
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

int	cpy_var(t_parse_cmd *p, int i, int *j, int size_name)
{
	int		o;
	int		k;
	int		size_var;

	k = 0;
	while (p->envp[k] != NULL)
	{
		if (ft_strncmp(p->envp[k], p->str_cmd + i + 1, size_name) == 0)
		{
			if (p->envp[k][size_name] == '=')
			{
				size_var = 0;
				while (p->envp[k][size_name + 1 + size_var] != '\0')
					size_var++;
				o = 0;
				while (p->envp[k][size_name + o + 1] != '\0')
				{
					p->buf[o + *j] = p->envp[k][size_name + o + 1];
					o++;
				}
				p->buf[o + *j] = '\0';
				*j = *j + size_var;
			}
			return (1);
		}
		k++;
	}
	return (-1);
}

int	fill_dollar(t_parse_cmd *p, int i, int *j, int to_escape)
{
	int		size_name;
	int		error;

	size_name = 0;
	if (p->str_cmd[i] == '$' && !to_escape && !ft_isalpha(p->str_cmd[i + 1])
		&& p->str_cmd[i] != '_')
	{
		p->buf[*j] = '$';
		p->buf[*j + 1] = '\0';
		*j = *j + 1;
	}
	else if (p->str_cmd[i] == '$' && !to_escape)
	{
		while (ft_isalnum(p->str_cmd[(i + 1) + size_name]))
			size_name++;
		error = cpy_var(p, i, j, size_name);
		if (error != -1)
			return (size_name);
	}
	return (size_name);
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

static void	fill_buf(t_parse_cmd *p, int len, int i)
{
	int		to_escape;
	int		name_size;
	int		j;

	j = 0;
	to_escape = 0;
	if (p->str_cmd[i] == '"')
	{
		i++;
		while (!(p->str_cmd[i] == '"' && !to_escape))
		{
			if (p->str_cmd[i] == '\\' && !to_escape)
				to_escape = 1;
			else
			{
				if (!is_meta_char_quote(p->str_cmd[i]) && to_escape)
				{
					p->buf[j] = '\\';
					j++;
					p->buf[j] = p->str_cmd[i];
					j++;

				}
				else if (!is_meta_char_quote(p->str_cmd[i]) || (is_meta_char_quote(p->str_cmd[i]) && to_escape))
				{
					p->buf[j] = p->str_cmd[i];
					j++;
				}
				name_size = fill_dollar(p, i, &j, to_escape);
				i += name_size;
				to_escape = 0;
			}
			i++;
		}
		i++;
	}
	else if (p->str_cmd[i] == '\'')
	{
		i++;
		while (p->str_cmd[i] != '\'')
		{
			p->buf[j] = p->str_cmd[i];
			j++;
			i++;
		}
	}
	else
	{
		while (i < len && p->str_cmd[i] != ' ' && !(p->str_cmd[i] == '|' && !to_escape))
		{
			if (p->str_cmd[i] == '\\' && !to_escape)
				to_escape = 1;
			else
			{
				if (!is_meta_char(p->str_cmd[i]) || (is_meta_char(p->str_cmd[i]) && to_escape))
				{
					p->buf[j] = p->str_cmd[i];
					j++;
				}
				name_size = fill_dollar(p, i, &j, to_escape);
				i += name_size;
				to_escape = 0;
			}
			i++;
		}
	}
	p->buf[j] = '\0';
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

int	dollar_size(t_parse_cmd p, int *size, int *i, int to_escape)
{
	int		size_name;
	int		size_value;
	int		j;

	size_name = 0;
	if (p.str_cmd[*i] == '$' && !to_escape && !ft_isalpha(p.str_cmd[*i + 1])
		&& p.str_cmd[*i] != '_')
	{
		*size = *size + 1;
		return (0);
	}
	if (p.str_cmd[*i] == '$' && !to_escape)
	{
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
		return (size_name);
	}
	return (0);
}

int	real_component_size(t_parse_cmd p, int i, int len)
{
	int		size;
	int		to_escape;

	to_escape = 0;
	size = 0;
	if (p.str_cmd[i] == '"')
	{
		size++;
		i++;
		while (i < len && !(p.str_cmd[i] == '"' && !to_escape))
		{
			if (p.str_cmd[i] == '\\' && !to_escape)
				to_escape = 1;
			else
				to_escape = 0;
			size++;
			i++;
		}
		size++;
	}
	else if (p.str_cmd[i] == '\'')
	{
		size++;
		i++;
		while (p.str_cmd[i] != '\'')
		{
			size++;
			i++;
		}
		size++;
	}
	else
	{
		while (i < len && p.str_cmd[i] != ' ' && !(p.str_cmd[i] == '|' && !to_escape)
			&& !(p.str_cmd[i] == '>' && !to_escape) && !(p.str_cmd[i] == '<' && !to_escape))
		{
			if (p.str_cmd[i] == '\\' && !to_escape)
				to_escape = 1;
			else
				to_escape = 0;
			size++;
			i++;
		}
	}
	return (size);
}

int	size_component_formated(t_parse_cmd p, int i, int len)
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
				i += name_size;
				to_escape = 0;
			}
			i++;
		}
		i++;
	}
	if (p.str_cmd[i] == '\'')
	{
		i++;
		while (p.str_cmd[i] != '\'')
		{
			i++;
			size++;
		}
		i++;
	}
	else
	{
		while (i < len && p.str_cmd[i] != ' ' && !(p.str_cmd[i] == '|' && !to_escape))
		{
			if (p.str_cmd[i] == '\\' && !to_escape)
			{
				to_escape = 1;
				size++;
			}
			else
			{
				if (!is_meta_char(p.str_cmd[i]))
					size++;
				name_size = dollar_size(p, &size, &i, to_escape);
				i += name_size;
				to_escape = 0;
			}
			i++;
		}
	}
	return (size);
}

static void	fill_redirection(t_parse_cmd *p, int *i, int len)
{
	
}

static char	**fill_args(t_parse_cmd *p, int *i, int len, int arg_nb)
{
	char		**args;
	int			size;
	int			j;

	args = init_args(arg_nb, *p);
	if (!args)
		return (0);
	j = 1;
	while (*i < len)
	{
		while (p->str_cmd[*i] == ' ')
			*i = *i + 1;
		if (p->str_cmd[*i] == '<' || p->str_cmd[*i] == '>')
			fill_redirection(p, *i, len);
		if (p->str_cmd[*i] == '|' || p->str_cmd[*i] == '\0' || *i >= len)
			return (args);
		size = size_component_formated(*p, *i, len);
		p->buf = malloc(sizeof(char) * size + 1);
		if (!p->buf)
			return (NULL);
		fill_buf(p, len, *i);
		args[j] = p->buf;
		p->buf = NULL;
		*i = *i + real_component_size(*p, *i, len);
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

static char	**parse_arguments(int *i, int size, int len, t_parse_cmd *p)
{
	int		arg_nb;
	char	**args;

	*i = *i + size;
	arg_nb = count_arg(p->str_cmd, *i, len);
	args = fill_args(p, i, len, arg_nb);
	printf("arg_nb = %d\n", arg_nb);
	exit(0);
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

static int	init_cmd_exe(int *i, t_parse_cmd *p, int len, int *size)
{
	t_cmd	*cmd;

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
	*size = size_component_formated(*p, *i, len);
	p->buf = malloc(sizeof(char) * (*size + 1));
	*size = real_component_size(*p, *i, len);
	if (!p->buf)
	{
		free(cmd);
		return (0);
	}
	fill_buf(p, len, *i);
	p->cmd->exe = p->buf;
	p->buf = NULL;
	while (p->str_cmd[*i] == ' ')
		*i = *i + 1;
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
		p.cmd->args = parse_arguments(&i, size, len, &p);
		if (!p.cmd->args)
		{
			free_cmd_content(p.first_cmd, p.first_cmd);
			free_cmd(p.first_cmd);
			return (NULL);
		}
		if (!set_previous_pipe(&p, &i) || i > len)
			break ;
	}
//	print_pipe(p.first_cmd);
	return (p.first_cmd);
}
