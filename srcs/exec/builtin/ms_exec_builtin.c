/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:37:09 by gcros             #+#    #+#             */
/*   Updated: 2024/05/28 16:12:32 by gcros            ###   ########.fr       */
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
	if (!shell->in_pipe)
	{
		waitpid(pid, &ret, 0);
		ms_set_status(ret);
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
