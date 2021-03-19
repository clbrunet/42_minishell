/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:04:47 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/19 21:47:51 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"
#include "main.h"

int				count_initial_elem(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

static char		**cpy_initial_envp(char **new_envp, char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

static void		add_new_var(t_cmd const *cmd, char **new_envp,
				int original_size, char **envp)
{
	int		i;
	int		j;
	int		exist;

	i = original_size;
	j = 1;
	while (cmd->args[j] != NULL)
	{
		if (is_name_valid(cmd->args[j]) == 1)
		{
			exist = var_exist(envp, cmd->args[j]);
			if (exist != 0)
			{
				free(new_envp[exist]);
				new_envp[exist] = ft_strdup(cmd->args[j]);
			}
			else if (is_only(cmd->args, j))
			{
				new_envp[i] = ft_strdup(cmd->args[j]);
				i++;
			}
		}
		j++;
	}
}

static void		print_sorted_var(char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i + 1] != NULL)
	{
		if (ft_strcmp(envp[i], envp[i + 1]) > 0)
		{
			tmp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(1, "declare -x ");
		ft_putstr_fd(1, envp[i]);
		ft_putstr_fd(1, "\n");
		i++;
	}
}

int				export_cmd(t_cmd const *cmd, char **envp_ptr[],
				int last_exit_code)
{
	int		count;
	int		original_size;
	char	**new_envp;
	int		exit_code;

	(void)last_exit_code;
	if (cmd->args[1] == NULL)
		print_sorted_var(*envp_ptr);
	exit_code = 0;
	count = count_valid_var(cmd->args, *envp_ptr, &exit_code);
	original_size = count_initial_elem(*envp_ptr);
	new_envp = malloc(sizeof(char *) * (count + original_size + 1));
	if (!new_envp)
		return (1);
	new_envp[count + original_size] = NULL;
	cpy_initial_envp(new_envp, *envp_ptr);
	add_new_var(cmd, new_envp, original_size, *envp_ptr);
	free_strs(*envp_ptr);
	*envp_ptr = new_envp;
	return (exit_code);
}
