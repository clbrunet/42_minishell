/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:57:07 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/21 06:25:08 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft.h"

static int	try_without_path(t_cmd const *cmd, char *envp[])
{
	int		fd;

	fd = open(cmd->exe, __O_PATH);
	if (fd < 0)
	{
		ft_putstr_fd(2, "minishell: ");
		ft_putstr_fd(2, cmd->exe);
		ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, "No such file or directory\n");
		return (127);
	}
	close(fd);
	execve(cmd->exe, cmd->args, envp);
	return (1);
}

static int	find_path_id(char *envp[])
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	try_launch_path(char *sub_path, char **argv, char **envp, char *cmd)
{
	char	*path;
	int		fd;

	path = create_path(sub_path, cmd);
	if (!path)
		return (1);
	fd = open(path, __O_PATH);
	if (fd < 0)
	{
		free(path);
		return (0);
	}
	close(fd);
	execve(path, argv, envp);
	free(path);
	return (1);
}

static int	try_path(t_cmd const *cmd, char *envp[], int *i, int path_id)
{
	int		size_sub_path;
	char	*sub_path;

	sub_path = create_sub_path(envp, *i, path_id, &size_sub_path);
	if (!sub_path)
		return (1);
	ft_strncpy(sub_path, envp[path_id] + *i, size_sub_path);
	if (try_launch_path(sub_path, cmd->args, envp, cmd->exe))
	{
		free(sub_path);
		return (1);
	}
	if (envp[path_id][*i + size_sub_path] == '\0')
		*i += size_sub_path;
	else
		*i += size_sub_path + 1;
	free(sub_path);
	return (0);
}

int			search_cmd(t_cmd const *cmd, char *envp[])
{
	int		path_id;
	int		i;

	path_id = find_path_id(envp);
	if (ft_strchr(cmd->exe, '/') || path_id == -1)
		return (try_without_path(cmd, envp));
	i = 4;
	while (envp[path_id][i] != '\n' && envp[path_id][i] != '\0')
	{
		if (try_path(cmd, envp, &i, path_id))
			return (1);
	}
	ft_putstr_fd(2, cmd->exe);
	ft_putstr_fd(2, ": command not found\n");
	return (127);
}
