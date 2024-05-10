/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 03:57:03 by gcros             #+#    #+#             */
/*   Updated: 2024/05/10 23:23:58 by gcros            ###   ########.fr       */
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
		return (-1);
	else if (pid == 0)
		exit(execbin(exec, shell));
	else
		return (parent(shell, pid));
	return (0);
}
