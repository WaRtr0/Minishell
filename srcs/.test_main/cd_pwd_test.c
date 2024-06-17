/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/05/10 23:47:11 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "ft_printf.h"
//#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

int	main(int ac, char **av, char **env)
{
	t_env	*envp;

	(void) ac;
	(void) av;
	(void) env;
	envp = NULL;
	ms_env_gen(env, &envp);
	cd(av, &envp);
	pwd(av);
	printf("PWD: %s\n", ms_env_get(envp, "PWD"));
	printf("OLDPWD: %s\n", ms_env_get(envp, "OLDPWD"));
	ms_env_collapse(&envp);
	return (0);
}
