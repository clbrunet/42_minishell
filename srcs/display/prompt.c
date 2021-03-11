/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:59:05 by clbrunet          #+#    #+#             */
/*   Updated: 2021/03/11 07:23:12 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ft.h"

static void	replace_home(char cwd[PATH_MAX], char *envp[])
{
	char	home_len;

	while (*envp)
	{
		if (ft_strncmp(*envp, "HOME=", 5) == 0)
		{
			home_len = ft_strlen(*envp + 5);
			if (ft_strncmp(*envp + 5, cwd, home_len) == 0)
			{
				cwd[0] = '~';
				ft_strcpy(cwd + 1, cwd + home_len);
			}
			return ;
		}
		envp++;
	}
}

/*	Print prompt with the current working directory then a symbol '$' to
	delimit from the command line.
	Return 1 if an error occurs. */

int	print_prompt(char *envp[], int last_exit_code)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	replace_home(cwd, envp);
	ft_putstr_fd(1, BOLD CYAN);
	ft_putstr_fd(1, cwd);
	if (last_exit_code == 0)
		ft_putstr_fd(1, GREEN " $ " RESET);
	else
		ft_putstr_fd(1, RED " $ " RESET);
	return (0);
}
