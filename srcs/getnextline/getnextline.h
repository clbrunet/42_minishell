/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:23:57 by mlebrun           #+#    #+#             */
/*   Updated: 2021/02/21 19:13:04 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETNEXTLINE_H
# define GETNEXTLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>

int			init_line(char **line);
int			update_buffer(int line_read, char *buffer, int i);
int			update_line(char **line, char *buffer);
int			getnextline(char **line);

int			ft_strlen(char *str);
void		ft_strcat(char *dest, char *src);
void		ft_strncat(char *dest, char *src, int n);
void		ft_strcpy(char *dest, char *src);

#endif
