/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:04:47 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/19 11:33:08 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"
#include "main.h"

#include <stdio.h>

int		is_name_valid(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (i == 0 && ft_isdigit(arg[i]))
			return (0);
		else if (i != 0)
		{
			if (!ft_isalnum(arg[i]) && arg[i] != '_')
				return (0);
		}
		i++;
	}
	if (arg[i] == '\0')
		return (-1);
	return (1);
}

int		size_env_name(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '=')
		i++;
	return (i);
}

int		var_exist(char **new_envp, char *arg)
{
	int		i;
	int		size_name;

	i = 0;
	while (new_envp[i] != NULL)
	{
		size_name = size_env_name(new_envp[i]);
		if (ft_strncmp(arg, new_envp[i], size_name) == 0)
			return (i);
		i++;		
	}
	return (0);
}

int		count_valid_var(char **args, char **envp, int *exit_code)
{
	int		count;
	int		i;
	int		name_valid;

	count = 0;
	i = 1;
	while (args[i] != NULL)
	{
		name_valid = is_name_valid(args[i]);
		if (name_valid == 1 && !var_exist(envp, args[i]))
			count++;
		else if (!name_valid)
		{
			ft_putstr_fd(2, "bash: export: `");
			ft_putstr_fd(2, args[i]);
			ft_putstr_fd(2, "': not a valid identifier\n");
			*exit_code = 1;
		}
		i++;
	}
	return (count);
}

int		count_initial_elem(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

char	**cpy_initial_envp(char **new_envp, char **envp)
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

void	add_new_var(t_cmd const *cmd, char **new_envp, int original_size, 
					char **envp)
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
			else
				new_envp[i] = ft_strdup(cmd->args[j]);
		}
		i++;
		j++;
	}
}

int	export_cmd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	int		count;
	int		original_size;
	char	**new_envp;
	int		exit_code;

	(void)last_exit_code;
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
