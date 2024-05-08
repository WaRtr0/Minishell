/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:53:13 by gcros             #+#    #+#             */
/*   Updated: 2024/05/03 04:40:33 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "env.h"

int	cd(char **args, t_env **env);
int	echo(char **args);
int	pwd(char **av);
int	env(char **av, t_env *env);
int	unset(char **av, t_env **env);
int	export(char **av, t_env **envp);

#endif