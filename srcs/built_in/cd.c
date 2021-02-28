/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:32:44 by mlebrun           #+#    #+#             */
/*   Updated: 2021/02/28 11:59:38 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int		cd()
{
	/*temporary variable (wait for parsing) */
	char	*path = "../fnem";

	if (printf("ret = %d", chdir(path) == -1))
		return (-1);
	return (1);
}
