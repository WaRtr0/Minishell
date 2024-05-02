/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:46:54 by gcros             #+#    #+#             */
/*   Updated: 2024/05/01 03:44:33 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <errno.h>
#include <stdio.h>

int		env_error(int err);
void	print_env(t_env *env);

int	env(int ac, char **av, t_env *env)
{
	(void) av;
	if (ac != 1)
		return (env_error(E2BIG));
	print_env(env);
	return (0);
}

void	print_env(t_env *env)
{
	if (env == NULL)
		return ;
	if (env->value)
		printf("%s=%s\n", env->key, env->value);
	print_env(env->left);
	print_env(env->right);
}

int	env_error(int err)
{
	if (err == E2BIG)
		printf("mishell: env: too many arguments\n");
	return (1);
}
