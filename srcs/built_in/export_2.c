/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:52:18 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/19 15:03:23 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int				is_name_valid(char *arg)
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

static int		size_env_name(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '=')
		i++;
	return (i);
}

int				var_exist(char **new_envp, char *arg)
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

int				count_valid_var(char **args, char **envp, int *exit_code)
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
