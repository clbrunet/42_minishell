/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 06:42:22 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/22 07:27:37 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <unistd.h>

size_t	ft_strlen(char const *str);
char	*ft_strcpy(char *dest, char const *src);
char	*ft_strcat(char *dest, char const *src);
char	*ft_strncat(char *dest, char const *src, size_t n);
void	ft_putstr(char *str);

#endif
