/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:33:47 by mlebrun           #+#    #+#             */
/*   Updated: 2021/02/21 20:09:41 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getnextline.h"

int	init_line(char **line)
{
	*line = malloc(sizeof(char) * (1));
	if (!line)
		return (0);
	line[0][0] = '\0';
	return (1);
}

int	update_buffer(int line_read, char *buffer, int i)
{
	char	*tmp;

	if (line_read)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(buffer + i + 1) + 1));
		if (!tmp)
			return (-1);
		ft_strcpy(tmp, (buffer + i + 1));
		ft_strcpy(buffer, tmp);
	}
	else
		buffer[0] = '\0';
	return (1);
}

int	update_line(char **line, char *buffer)
{
	int		i;
	int		line_read;
	int		size_line;
	int		size_lbuf;
	char	*tmp;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line_read = 0;
	if (buffer[i] == '\n')
		line_read = 1;
	size_line = ft_strlen(*line);
	tmp = malloc(sizeof(char) * (i + size_line + 1));
	if (!tmp)
		return (-1);
	ft_strcpy(tmp, *line);
	ft_strncat(tmp, buffer, i);
	free(*line);
	*line = tmp;
	if (update_buffer(line_read, buffer, i) == -1)
		return (-1);
	return (line_read);
}

int	getnextline(char **line)
{
	static char		buffer[1001] = {0};
	int				byte_read;
	int				error;

	if (!init_line(line))
		return (-1);
	if (*buffer)
	{
		error = update_line(line, buffer);
		if (error == 1 || error == -1)
			return (error);
	}
	byte_read = 1;
	while (byte_read)
	{
		byte_read = read(0, buffer, 1000);
		if (byte_read == -1)
			return (-1);
		buffer[byte_read] = '\0';
		error = update_line(line, buffer);
		if (error == -1 || error == 1)
			return (error);
	}
	return (0);
}
