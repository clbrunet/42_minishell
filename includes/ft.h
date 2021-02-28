/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 06:42:22 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/27 15:29:41 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <unistd.h>
# include <stdlib.h>

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

#endif
