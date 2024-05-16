/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:53:13 by gcros             #+#    #+#             */
/*   Updated: 2024/05/11 04:22:59 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "env.h"
# include "minishell.h"

int	cd(char **args, t_env **env);
int	echo(char **args);
int	pwd(char **av);
int	env(char **av, t_env *env);
int	unset(char **av, t_env **env);
int	export(char **av, t_env **envp);
int	b_exit(t_exec *exec, t_shell *shell);

#endif