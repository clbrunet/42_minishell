/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:26:28 by mlebrun           #+#    #+#             */
/*   Updated: 2021/02/28 18:52:27 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <stdio.h>
# include <unistd.h>

# include "cmd.h"

typedef int	(*built_in_ft)(t_cmd *cmd);

built_in_ft	search_built_in(t_cmd *cmd);

int			echo(t_cmd *cmd);
int			cd(t_cmd *cmd);

#endif
