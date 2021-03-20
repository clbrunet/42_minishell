/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:29:40 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/20 19:59:54 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ft.h"

static int	strcmp_until_equal(const char *s1, const char *s2)
{
	const unsigned char	*u_s1;
	const unsigned char	*u_s2;

	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while (*u_s1 && *u_s1 != '=' && *u_s1 == *u_s2)
	{
		u_s1++;
		u_s2++;
	}
	if (*u_s1 == '=')
		return ((int)(0 - *u_s2));
	else if (*u_s2 == '=')
		return ((int)(*u_s1 - 0));
	return ((int)(*u_s1 - *u_s2));
}

static void	copy_envp(char **sorted_vars, char **envp)
{
	while (*envp)
	{
		*sorted_vars = *envp;
		sorted_vars++;
		envp++;
	}
	*sorted_vars = *envp;
}

static void	sort_sorted_vars(char **sorted_vars)
{
	char	*tmp;
	char	**backup;

	if (*sorted_vars == NULL)
		return ;
	backup = sorted_vars;
	while (sorted_vars[1] != NULL)
	{
		if (strcmp_until_equal(sorted_vars[0], sorted_vars[1]) > 0)
		{
			tmp = sorted_vars[0];
			sorted_vars[0] = sorted_vars[1];
			sorted_vars[1] = tmp;
			sorted_vars = backup;
		}
		else
			sorted_vars++;
	}
}

void		print_var(char *var)
{
	ft_putstr_fd(1, "declare -x ");
	while (*var != '=')
	{
		ft_putchar_fd(1, *var);
		var++;
	}
	ft_putstr_fd(1, "=\"");
	var++;
	ft_putstr_fd(1, var);
	ft_putstr_fd(1, "\"\n");
}

int			print_sorted_vars(char **envp, int original_size)
{
	char	**sorted_vars;
	int		i;

	sorted_vars = malloc((original_size + 1) * sizeof(char *));
	if (sorted_vars == NULL)
		return (1);
	copy_envp(sorted_vars, envp);
	sort_sorted_vars(sorted_vars);
	i = 0;
	while (sorted_vars[i] != NULL)
	{
		print_var(sorted_vars[i]);
		i++;
	}
	free(sorted_vars);
	return (0);
}
