/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:12:15 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/19 21:46:24 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"
#include "main.h"

static int		var_exist_unset(char **envp, char *arg)
{
	int		i;
	int		size_name;

	i = 0;
	while (envp[i] != NULL)
	{
		size_name = ft_strlen(arg);
		if (ft_strncmp(arg, envp[i], size_name) == 0)
		{
			if (envp[i][size_name] == '=')
				return (1);
		}
		i++;
	}
	return (0);
}

static int		count_to_unset(char **args, char **envp, int *exit_code)
{
	int		i;
	int		count;
	int		name_valid;

	i = 1;
	count = 0;
	while (args[i] != NULL)
	{
		name_valid = is_name_valid_unset(args[i]);
		if (name_valid == 1 && var_exist_unset(envp, args[i])
			&& !already_deleted(args, i))
		{
			count++;
		}
		if (!name_valid)
		{
			ft_putstr_fd(2, "bash: unset: `");
			ft_putstr_fd(2, args[i]);
			ft_putstr_fd(2, "': not a valid identifier'\n");
			*exit_code = 1;
		}
		i++;
	}
	return (count);
}

static int		to_delete(char *env, char **arg)
{
	int		i;
	int		size_name;

	i = 1;
	while (arg[i] != NULL)
	{
		if (is_name_valid_unset(arg[i]))
		{
			size_name = ft_strlen(arg[i]);
			if (ft_strncmp(env, arg[i], size_name) == 0)
			{
				if (env[size_name] == '=')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

static void		fill_new_envp(char **new_envp, char **envp, char **arg)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
	{
		if (!to_delete(envp[i], arg))
		{
			new_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
}

int				unset(t_cmd const *cmd, char **envp_ptr[], int last_exit_code)
{
	int		count;
	int		size_initial;
	int		exit_code;
	char	**new_envp;

	(void)last_exit_code;
	exit_code = 0;
	count = count_to_unset(cmd->args, *envp_ptr, &exit_code);
	size_initial = count_initial_elem(*envp_ptr);
	new_envp = malloc(sizeof(char *) * ((size_initial - count) + 1));
	if (!new_envp)
		return (1);
	new_envp[size_initial - count] = NULL;
	fill_new_envp(new_envp, *envp_ptr, cmd->args);
	free_strs(*envp_ptr);
	*envp_ptr = new_envp;
	return (exit_code);
}
