/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:03:53 by gcros             #+#    #+#             */
/*   Updated: 2024/06/04 11:07:46 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "env.h"
#include <errno.h>
#include <stdio.h>
#include "str.h"
#include "put.h"

static int	cd_getop(char *path, t_env *env, char **op);
static int	cd_error(int err, char *path);
static int	cd_update_env(t_env	**env);

int	cd(char **args, t_env **env)
{
	char	*op;
	int		err;

	if (args[0] && args[1] && args[2])
		return (cd_error(E2BIG, NULL));
	if (cd_getop(args[1], *env, &op) == 1)
		return (EXIT_FAILURE);
	err = chdir(op);
	if (err == -1)
		return (cd_error(errno, op));
	if (cd_update_env(env))
	{
		cd_error(errno, op);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
			ft_putstr_fd("mishell: cd: HOME not set\n", 2);
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
	char	*err_msg;

	if (err == EACCES)
		err_msg = ft_strsjoin((char *[])
			{"mishell: cd: ", path, ": Permission denied", NULL});
	else if (err == ENAMETOOLONG)
		err_msg = ft_strsjoin((char *[])
			{"mishell: cd: ", path, ": Path too long", NULL});
	else if (err == ENOENT || err == ENOTDIR)
		err_msg = ft_strsjoin((char *[])
			{"mishell: cd: ", path, ": No such file or directory", NULL});
	else if (err == E2BIG)
		err_msg = ft_strsjoin((char *[])
			{"mishell: cd: too many arguments", NULL});
	else
		err_msg = ft_strsjoin((char *[])
			{"mishell: cd: ", path, ": good luck", NULL});
	if (err_msg)
		ft_putendl_fd(err_msg, 2);
	free(err_msg);
	return (EXIT_FAILURE);
}
