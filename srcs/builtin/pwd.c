/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 04:53:09 by gcros             #+#    #+#             */
/*   Updated: 2024/05/11 04:45:16 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "put.h"

int	pwd_error(int err, char *op);

int	pwd(char **av)
{
	char	*pwd;

	if (av[0] && av[1] && av[1][0] == '-' && av[1][1] != '\0')
		return (pwd_error(EINVAL, av[1]));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (pwd_error(errno, NULL));
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

int	pwd_error(int err, char *op)
{
	char	*err_msg;

	if (err == EACCES)
		ft_putendl_fd("mishell: pwd: Permission denied", 2);
	else if (err == ENAMETOOLONG)
		ft_putendl_fd("mishell: pwd: Path too long", 2);
	else if (err == ENOENT || err == ENOTDIR)
		ft_putendl_fd("mishell: pwd: No such file or directory", 2);
	else if (err == EINVAL)
	{
		err_msg = ft_strsjoin((char *[])
			{"mishell: pwd: ", op, ": invalid option", NULL});
		if (err_msg)
			ft_putendl_fd(err_msg, 2);
		free(err_msg);
	}
	else
		ft_putendl_fd("mishell: pwd: good luck\n", 2);
	return (EXIT_FAILURE);
}