/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:30:10 by clbrunet          #+#    #+#             */
/*   Updated: 2021/02/19 21:22:03 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	main(int argc, char *argv[], char *envp[])
{
	/* char	*command; */

	(void)argc;
	(void)argv;
	(void)envp;
	if (print_prompt())
		return (1);
	return (0);
}
