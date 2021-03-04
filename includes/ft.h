/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 06:42:22 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/04 11:54:10 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <unistd.h>
# include <stdlib.h>

# include "cmd.h"

size_t	ft_strlen(char const *str);
char	*ft_strcpy(char *dest, char const *src);
char	*ft_strncpy(char *dest, char const *src, int n);
char	*ft_strcat(char *dest, char const *src);
char	*ft_strncat(char *dest, char const *src, size_t n);
void	ft_putstr(char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
void	ft_putstr_fd(int fd, char const *str);
void	ft_putchar_fd(int fd, char const c);
char	*ft_strndup(char const *s, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_lstsize(t_cmd const *lst);
char	*ft_strdup(char const *s);

#endif
