/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:20:50 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/18 07:14:10 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_strs(char **strs)
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

int		malloc_envp(char **envp_original_ptr[])
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
