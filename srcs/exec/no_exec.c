/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:23:23 by gcros             #+#    #+#             */
/*   Updated: 2024/06/17 12:36:36 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	parent(t_shell *shell, int pid);

int	run_no_exec(t_exec *exec)
{
	if (get_redir(exec))
		return (1);
	close_fds(exec->dfl_fds);
	return (0);
}

int	exec_no_exec(t_exec *exec, t_shell *shell)
{
	int		ret;

	ret = run_no_exec(exec);
	free_shell(shell);
	free_exec(exec);
	return (ret);
}

int	fork_no_exec(t_exec *exec, t_shell *shell)
{
	int	pid;

	if (!shell->in_pipe)
		return (run_no_exec(exec) << 8);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE << 8);
	else if (pid == 0)
		exit(exec_no_exec(exec, shell));
	else
		return (parent(shell, pid));
	return (EXIT_FAILURE << 8);
}
