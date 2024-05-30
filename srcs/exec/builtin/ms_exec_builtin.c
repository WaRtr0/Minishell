/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:37:09 by gcros             #+#    #+#             */
/*   Updated: 2024/05/30 15:36:19 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "exec.h"
#include <errno.h>

int	parent(t_shell *shell, int pid);
int	child(t_exec *exec, t_shell *shell);

int	ms_exec_builtin(t_exec *exec, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		exit(child(exec, shell));
	else
		return (parent(shell, pid));
	return (EXIT_FAILURE);
}

int	parent(t_shell *shell, int pid)
{
	int	ret;

	ret = 0;
	shell->last_pid = pid;
	if (!shell->in_pipe)
	{
		waitpid(shell->last_pid, &ret, 0);
	}
	return (ret);
}

int	child(t_exec *exec, t_shell *shell)
{
	int	ret;
	size_t	i;

	ret = ms_run_builtin(exec, shell);
	free_shell(shell);
	free_exec(exec);
	i = 3;
	while (i < 1024)
		close(i++);
	return (ret);
}
