/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:13:04 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/17 15:56:12 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_redirection	*create_red(char *path_or_endstr)
{
	t_redirection		*red;

	red = malloc(sizeof(t_redirection) * (1));
	if (!red)
		return (NULL);
	red->next = NULL;
	red->path_or_endstr = path_or_endstr;
	red->next = NULL;
	red->type = NONE;
	return (red);
}

static void				add_out_red(t_parse_cmd *p,
					t_redirection_type red_type, char *path_or_endstr)
{
	t_redirection	*first_red;
	t_redirection	*red;

	red = create_red(path_or_endstr);
	first_red = p->cmd->out_redirection;
	while (p->cmd->out_redirection && p->cmd->out_redirection->next != NULL)
		p->cmd->out_redirection = p->cmd->out_redirection->next;
	if (red_type == 1)
		red->type = SIMPLE;
	else
		red->type = DOUBLE;
	if (p->cmd->out_redirection)
		p->cmd->out_redirection->next = red;
	else
		p->cmd->out_redirection = red;
	if (first_red != NULL)
		p->cmd->out_redirection = first_red;
}

static void				add_in_red(t_parse_cmd *p, t_redirection_type red_type,
					char *path_or_endstr)
{
	t_redirection	*first_red;
	t_redirection	*red;

	red = create_red(path_or_endstr);
	first_red = p->cmd->in_redirection;
	while (p->cmd->in_redirection && p->cmd->in_redirection->next != NULL)
		p->cmd->in_redirection = p->cmd->in_redirection->next;
	if (red_type == 1)
		red->type = SIMPLE;
	else
		red->type = DOUBLE;
	if (p->cmd->in_redirection)
		p->cmd->in_redirection->next = red;
	else
		p->cmd->in_redirection = red;
	if (first_red != NULL)
		p->cmd->in_redirection = first_red;
}

void					add_red(t_parse_cmd *p, char *path_or_endstr,
						int in_out, t_redirection_type red_type)
{
	if (in_out)
		add_out_red(p, red_type, path_or_endstr);
	else
		add_in_red(p, red_type, path_or_endstr);
}

void					determine_in_type(t_parse_cmd *p, int *in_out, int *i,
				t_redirection_type *red_type)
{
	*in_out = 1;
	*i = *i + 1;
	if (p->str_cmd[*i] == '>')
	{
		*i = *i + 1;
		*red_type = DOUBLE;
	}
	else
		*red_type = SIMPLE;
}
