/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 07:28:12 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ft.h"
#include "parsing.h"
#include "built_in.h"
#include "execution.h"

static void	free_strs(char **strs)
{
	char	**iter;

	if (strs == NULL)
		return ;
	iter = strs;
	while (*iter)
	{
		free(*iter);
		iter++;
	}
	free(strs);
}

static int	malloc_envp(char **envp_original_ptr[])
{
	char	**envp;
	char	**iter;

	iter = *envp_original_ptr;
	while (*iter)
		iter++;
	envp = malloc((iter - *envp_original_ptr + 1) * sizeof(char *));
	if (envp == NULL)
		return (1);
	iter = *envp_original_ptr;
	*envp_original_ptr = envp;
	while (*iter)
	{
		*envp = ft_strdup(*iter);
		if (*envp == NULL)
		{
			free_strs(*envp_original_ptr);
			return (1);
		}
		envp++;
		iter++;
	}
	*envp = NULL;
	return (0);
}

static int	main_end(int line_read, char *envp[])
{
	free_strs(envp);
	if (line_read == -1)
		return (1);
	else
		ft_putstr_fd(1, "exit\n");
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		line_read;
	int		last_exit_code;

	(void)argv;
	last_exit_code = 0;
	if (argc != 1 || print_prompt(envp, last_exit_code) || malloc_envp(&envp))
		return (1);
	line_read = get_next_line(&line);
	while (line_read == 1)
	{
		execute_cmds(line, &envp, &last_exit_code);
		if (print_prompt(envp, last_exit_code))
		{
			free_strs(envp);
			return (1);
		}
		line_read = get_next_line(&line);
	}
	return (main_end(line_read, envp));
}
