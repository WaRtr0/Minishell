/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 03:57:03 by gcros             #+#    #+#             */
/*   Updated: 2024/06/12 18:48:59 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "str.h"

int	parent(t_shell *shell, int pid);

int	ms_exec_bin(t_exec *exec, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE << 8);
	else if (pid == 0)
		exit(execbin(exec, shell));
	else
		return (parent(shell, pid));
	return (EXIT_FAILURE << 8);
}
