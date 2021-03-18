/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 06:56:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/18 07:14:36 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <signal.h>

# include "display.h"
# include "ft.h"
# include "parsing.h"
# include "execution.h"

void	free_strs(char **strs);
int		malloc_envp(char **envp_original_ptr[]);

void	reading_int_handler(int signum);
void	execution_int_handler(int signum);
void	reading_quit_handler(int signum);
void	execution_quit_handler(int signum);

#endif
