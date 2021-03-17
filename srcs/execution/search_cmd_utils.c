/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:32:12 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/17 18:32:23 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft.h"

char	*create_path(char *sub_path, char *cmd)
{
	int		size_cmd;
	int		size_sub_path;
	char	*path;
	int		slash_ended;

	size_sub_path = ft_strlen(sub_path);
	size_cmd = ft_strlen(cmd);
	slash_ended = 1;
	if (sub_path[size_sub_path - 1] == '/')
		slash_ended = 0;
	path = malloc(sizeof(char) * (size_sub_path + size_cmd + slash_ended + 1));
	if (!path)
		return (NULL);
	ft_strcpy(path, sub_path);
	if (slash_ended)
		ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}

char	*create_sub_path(char **envp, int i, int path_id,
		int *size_sub_path)
{
	char	*sub_path;

	*size_sub_path = 0;
	while (envp[path_id][i + *size_sub_path] != ':' && envp[path_id][i
			+ *size_sub_path] != '\0')
		*size_sub_path = *size_sub_path + 1;
	sub_path = malloc(sizeof(char) * (*size_sub_path + 1));
	return (sub_path);
}
