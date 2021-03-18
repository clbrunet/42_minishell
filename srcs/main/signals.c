/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 06:52:14 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/18 07:16:47 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	reading_int_handler(int signum)
{
	if (signal(signum, SIG_IGN) != SIG_ERR)
	{
		ft_putchar_fd(1, '\n');
		print_prompt(130);
		signal(SIGINT, reading_int_handler);
	}
}

void	execution_int_handler(int signum)
{
	if (signal(signum, SIG_IGN) != SIG_ERR)
	{
		ft_putchar_fd(1, '\n');
		signal(SIGINT, execution_int_handler);
	}
}

void	reading_quit_handler(int signum)
{
	if (signal(signum, SIG_IGN) != SIG_ERR)
	{
		ft_putstr_fd(1, "\b\b  \b\b");
		signal(SIGQUIT, reading_quit_handler);
	}
}

void	execution_quit_handler(int signum)
{
	if (signal(signum, SIG_IGN) != SIG_ERR)
	{
		ft_putstr_fd(1, "Quit (core dumped)\n");
		signal(SIGQUIT, execution_quit_handler);
	}
}
