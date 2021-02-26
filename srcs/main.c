/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/26 14:17:58 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parsing.h"
#include "ft.h"
#include <errno.h>

int		find_path_id(char *envp[])
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

char	*create_path(char *sub_path, char *cmd)
{
	int		size_cmd;
	int		size_sub_path;
	char	*path;
	int		slash_ended;

	size_sub_path = ft_strlen(sub_path);
	size_cmd = ft_strlen(cmd);
	slash_ended = 0;
	if (sub_path[size_sub_path - 1] == '/')
		slash_ended = 1;
	path = malloc(sizeof(char) * (size_sub_path + size_cmd + slash_ended + 1));
	if (!path)
		return (NULL);
	ft_strcpy(path, sub_path);
	if (!slash_ended)
		ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}

int		try_path(char *sub_path, char **argv, char **envp, char *cmd)
{
	int		pid;
	int		error;
	char	*path;
	int		fd;

	path = create_path(sub_path, cmd);
	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	pid = fork();
	if (pid == 0)
	{
		error = execve(path, argv, envp);
		if (error == -1)
			return (-1);
	}
	wait(NULL);
	return (1);
}

int		find_exec(char *envp[], char *cmd)
{
	int		path_id;
	int		size_sub_path;
	char	*sub_path;
	int		i;
	char	*argv_test[] = {"pwd", NULL};

	path_id = find_path_id(envp);
	if (path_id == -1)
		return (0);
	i = 4;
	while (envp[path_id][i] != '\n' && envp[path_id][i] != '\0')
	{
		size_sub_path = 0;
		while (envp[path_id][i + size_sub_path] != ':' && envp[path_id][i + size_sub_path] != '\0')
			size_sub_path++;
		sub_path = malloc(sizeof(char) * (size_sub_path + 1));
		if (!sub_path)
			return (-1);
		ft_strncpy(sub_path, envp[path_id] + i, size_sub_path);
		if (try_path(sub_path, argv_test, envp, cmd))
			return (1);
		if (envp[path_id][i + size_sub_path] == '\0')
			i += size_sub_path;
		else
			i += size_sub_path + 1;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		line_read;

	(void)argc;
	(void)argv;
	(void)envp;
	line_read = 1;
	while (line_read == 1)
	{
		if (print_prompt())
			return (1);
		line_read = get_next_line(&line);
		find_exec(envp, "pwd");
	}
	if (line_read == -1)
		return (1);
	return (0);
}
