/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 04:53:09 by gcros             #+#    #+#             */
/*   Updated: 2024/04/24 05:09:25 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int	pwd_error(int err, char *op);

int	pwd(int ac, char **av)
{
	char	*pwd;

	if (ac != 1 && av[1][0] == '-' && av[1][1] != '\0')
		return (pwd_error(EINVAL, av[1]));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (pwd_error(errno, NULL));
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	pwd_error(int err, char *op)
{
	if (err == EACCES)
		printf("mishell: pwd: Permission denied\n");
	else if (err == ENAMETOOLONG)
		printf("mishell: pwd: Path too long\n");
	else if (err == ENOENT || err == ENOTDIR)
		printf("mishell: pwd: No such file or directory\n");
	else if (err == EINVAL)
		printf("mishell: pwd: %s: invalid option\n", op);
	else
		printf("mishell: pwd: good luck\n");
	return (1);
}