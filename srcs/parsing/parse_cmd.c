/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 07:16:13 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/21 11:02:14 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

static t_cmd	*init_cmd(t_parse_cmd *p, int *i)
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
	p->cmd->in_redirection = NULL;
	p->cmd->out_redirection = NULL;
	return (cmd);
}

static int		init_cmd_exe(int *i, t_parse_cmd *p, int len, int *size)
{
	t_cmd	*cmd;

	cmd = init_cmd(p, i);
	if (!cmd)
		return (0);
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

static void		init_parsing(t_parse_cmd *p, char const *str_cmd,
				char **envp, int last_exit_code)
{
	p->p_cmd = NULL;
	p->first_cmd = NULL;
	p->str_cmd = str_cmd;
	p->envp = envp;
	p->last_exit_code = last_exit_code;
}

t_cmd			*parse_cmd(char const *str_cmd, int len, char **envp[],
				int last_exit_code)
{
	int				i;
	int				size;
	t_parse_cmd		p;

	i = 0;
	init_parsing(&p, str_cmd, *envp, last_exit_code);
	while (1)
	{
		if (!init_cmd_exe(&i, &p, len, &size))
			return (NULL);
		p.cmd->args = parse_arguments(&i, size, len, &p);
		if (!p.cmd->args)
		{
			free_cmd(p.first_cmd);
			return (NULL);
		}
		if (!set_previous_pipe(&p, &i) || i > len)
			break ;
	}
	return (p.first_cmd);
}
