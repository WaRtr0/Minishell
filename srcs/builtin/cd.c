/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:03:53 by gcros             #+#    #+#             */
/*   Updated: 2024/04/23 23:50:54 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "env.h"
#include <errno.h>
#include <stdio.h>
#include "str.h"

static int	cd_getop(char *path, t_env *env, char **op);
static int	cd_error(int err, char *path);
static int	cd_update_env(t_env	**env);

int	cd(int ac, char **args, t_env **env)
{
	char	*op;
	int		err;

	if (ac > 2)
		return (cd_error(E2BIG, NULL));
	if (cd_getop(args[1], *env, &op) == 1)
		return (1);
	err = chdir(op);
	if (err == -1)
		return (cd_error(errno, op));
	if (cd_update_env(env))
		return (1);
	return (0);
}

static int	cd_update_env(t_env	**env)
{
	char	*pwdv;

	pwdv = ms_env_get(*env, "PWD");
	if (ms_env_exist(*env, "OLDPWD") == 1)
		if (ms_env_append(env, "OLDPWD", pwdv) == 1)
			return (1);
	if (ms_env_exist(*env, "PWD") == 1)
	{
		pwdv = getcwd(NULL, 0);
		if (pwdv == NULL)
			return (1);
		if (ms_env_append(env, "PWD", pwdv) == 1)
		{
			free(pwdv);
			return (1);
		}
		free(pwdv);
	}
	return (0);
}

static int	cd_getop(char *path, t_env *env, char **op)
{
	if (path == NULL)
	{
		*op = ms_env_get(env, "HOME");
		if (*op == NULL)
		{
			write(2, "mishell: cd: HOME not set\n",
				sizeof("mishell: cd: HOME not set\n"));
			return (1);
		}
	}
	else if (*path == '\0')
		*op = ".";
	else
		*op = path;
	return (0);
}

static int	cd_error(int err, char *path)
{
	if (err == EACCES)
		printf("mishell: cd: %s: Permission denied\n", path);
	else if (err == ENAMETOOLONG)
		printf("mishell: cd: %s: Path too long\n", path);
	else if (err == ENOENT || err == ENOTDIR)
		printf("mishell: cd: %s: No such file or directory\n", path);
	else if (err == E2BIG)
		printf("mishell: cd: too many arguments\n");
	else
		printf("mishell: cd: %s: good luck\n", path);
	return (1);
}
