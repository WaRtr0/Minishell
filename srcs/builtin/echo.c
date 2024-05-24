/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:33:39 by gcros             #+#    #+#             */
/*   Updated: 2024/05/24 18:24:33 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "put.h"
#include <stdio.h>
#include "conf.h"

int	jump_nflags(char **args, int *njumps);
int	is_nflags(char *str);

int	echo(char **args)
{
	int	offset;
	int	eol;

	offset = 1;
	eol = 1;
	if (jump_nflags(args, &offset))
		eol = 0;
	while (args[offset] != NULL)
	{
		ft_putstr_fd(args[offset], 1);
		if (args[++offset] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (eol)
		write (1, "\n", 1);
	return (0);
}

int	jump_nflags(char **args, int *njumps)
{
	int	j;

	j = 1;
	while (args[j] && is_nflags(args[j]))
	{
		if (DEBUG_MODE)
			printf("===echo %d\n", j);
		j++;
	}
	*njumps = j;
	return (j > 1);
}

int	is_nflags(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}
