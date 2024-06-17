/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_io_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:08:42 by gcros             #+#    #+#             */
/*   Updated: 2024/06/17 12:11:17 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "conf.h"

int	set_io(int old[2])
{
	if (DEBUG_MODE)
		printf("===set %d as input\n", old[0]);
	if (DEBUG_MODE)
		printf("===set %d as output\n", old[1]);
	dup2(old[0], 0);
	dup2(old[1], 1);
	return (0);
}

int	save_io(int old[2], int new[2])
{
	new[0] = dup(old[0]);
	new[1] = dup(old[1]);
	if (DEBUG_MODE)
		printf("===save to %d as input\n", new[0]);
	if (DEBUG_MODE)
		printf("===save to %d as output\n", new[1]);
	return (0);
}

int	restore_io(int old[2])
{
	dup2(old[0], 0);
	dup2(old[1], 1);
	if ((old[0] | 1) != 1)
		close(old[0]);
	if ((old[1] | 1) != 1)
		close(old[1]);
	if (DEBUG_MODE)
		printf("===restore from %d as input\n", old[0]);
	if (DEBUG_MODE)
		printf("===restore from %d as output\n", old[1]);
	return (0);
}

void	close_fds(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}
