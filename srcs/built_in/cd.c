/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:32:44 by mlebrun           #+#    #+#             */
/*   Updated: 2021/02/28 18:33:41 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/* path: temporary variable (wait for parsing) */

int	cd(t_cmd *cmd)
{
	char	*path = "../fnem";

	(void)cmd;
	if (printf("ret = %d", chdir(path) == -1))
		return (-1);
	return (1);
}
