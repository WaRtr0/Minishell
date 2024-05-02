/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:33:39 by gcros             #+#    #+#             */
/*   Updated: 2024/04/24 01:51:40 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdio.h>

int	jump_nflags(char **args, int *njumps);

int	echo(char **args)
{
	int		offset;
	char	eol;

	offset = 0;
	eol = '\n';
	if (jump_nflags(args, &offset))
		eol = '\0';
	while (args[offset] != NULL)
	{
		printf("%s", (args[offset]));
		if (args[++offset] != NULL)
			printf(" ");
	}
	printf("%c", eol);
	return (0);
}

int	jump_nflags(char **args, int *njumps)
{
	int	j;

	j = 0;
	while (args[j] && ft_strncmp(args[j], "-n", 3) == 0)
		j++;
	*njumps = j;
	return (j != 0);
}
