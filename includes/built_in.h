/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:26:28 by mlebrun           #+#    #+#             */
/*   Updated: 2021/03/19 21:49:31 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <unistd.h>

# include "cmd.h"

int		echo(t_cmd const *cmd, char **envp_ptr[], int last_exit_code);
int		cd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code);
int		env(t_cmd const *cmd, char **envp_ptr[], int last_exit_code);
int		exit_cmd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code);

int		export_cmd(t_cmd const *cmd, char **envp_ptr[], int last_exit_code);
int		is_name_valid(char *arg);
int		var_exist(char **envp, char *arg);
int		count_valid_var(char **args, char **envp, int *exit_code);
int		count_initial_elem(char **envp);
int		size_env_name(char *arg);
int		is_only(char **args, int i);

int		unset(t_cmd const *cmd, char **envp_ptr[], int last_exit_code);
int		is_name_valid_unset(char *arg);
int		already_deleted(char **args, int i);
#endif
