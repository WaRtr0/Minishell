/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:53:13 by gcros             #+#    #+#             */
/*   Updated: 2024/05/01 02:36:29 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "env.h"

int	cd(int ac, char **args, t_env **env);
int	echo(char **args);
int	pwd(int ac, char **av);
int	env(int ac, char **av, t_env *env);
int	unset(int ac, char **av, t_env **env);
int	export(char **av, t_env **envp);

#endif