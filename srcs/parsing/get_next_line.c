/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:33:47 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/17 08:32:15 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft.h"

static int	init(char **line, int *byte_read)
{
	*byte_read = 1;
	*line = malloc(sizeof(char) * (1));
	if (!line)
		return (0);
	line[0][0] = '\0';
	return (1);
}

static int	count_byte(int *line_read, char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		*line_read = 1;
	return (i);
}

static int	update_line(char **line, char *buffer)
{
	int		i;
	int		line_read;
	int		size_line;
	char	*tmp;

	line_read = 0;
	i = count_byte(&line_read, buffer);
	size_line = ft_strlen(*line);
	tmp = malloc(sizeof(char) * (i + size_line + 1));
	if (!tmp)
	{
		free(*line);
		return (-1);
	}
	ft_strcpy(tmp, *line);
	ft_strncat(tmp, buffer, i);
	free(*line);
	*line = tmp;
	if (line_read)
		ft_strcpy(buffer, buffer + i + 1);
	else
		*buffer = 0;
	return (line_read);
}

static int	finish_buffer(char **line, char *buffer)
{
	int		error;

	if (*buffer)
	{
		error = update_line(line, buffer);
		if (error == 1 || error == -1)
			return (error);
	}
	return (0);
}

int			get_next_line(char **line)
{
	static char		buffer[1001] = {0};
	int				byte_read;
	int				error;

	if (!init(line, &byte_read))
		return (-1);
	error = finish_buffer(line, buffer);
	if (error == 1 || error == -1)
		return (error);
	while (byte_read || **line)
	{
		byte_read = read(0, buffer, 1000);
		if (byte_read == -1)
		{
			free(*line);
			return (-1);
		}
		buffer[byte_read] = '\0';
		error = update_line(line, buffer);
		if (error == -1 || error == 1)
			return (error);
	}
	free(*line);
	*line = NULL;
	return (0);
}
