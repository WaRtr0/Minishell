/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:37:09 by gcros             #+#    #+#             */
/*   Updated: 2024/05/07 01:28:18 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"

int	parent(t_shell *shell, int pid);
int	child(t_exec *exec, t_shell *shell);

int	ms_exec_builtin(t_exec *exec, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
		exit(child(exec, shell));
	else
		return (parent(shell, pid));
	return (0);
}

int	parent(t_shell *shell, int pid)
{
	int	ret;

	ret = 0;
	if (!shell->in_pipe)
	{
		waitpid(pid, &ret, 0);
	}
	return (ret);
}

int	child(t_exec *exec, t_shell *shell)
{
	int	ret;

	ret = ms_run_builtin(exec, shell);
	free_shell(shell);
	free_exec(exec);
	exit(ret);
}
