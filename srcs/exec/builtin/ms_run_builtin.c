/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_run_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/24 18:32:41 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtin.h"
#include "exec.h"
#include "put.h"
#include "conf.h"

int	run_bti(t_exec *exec, t_shell *shell);

int	ms_run_builtin(t_exec *exec, t_shell *shell)
{
	int	save_fd[2];
	int	ret;

	save_io((int [2]){0, 1}, save_fd);
	save_io((int [2]){0, 1}, save_fd);
	set_io(exec->fd);
	ret = run_bti(exec, shell);
	restore_io(save_fd);
	return (ret);
}

int	run_bti(t_exec *exec, t_shell *shell)
{
	if (DEBUG_MODE)
		printf("==%s==\n", (char *)exec->content->data[0]);
	if (ft_strncmp(exec->content->data[0], "cd", 3) == 0)
		return (cd((char **)exec->content->data, &shell->env));
	if (ft_strncmp(exec->content->data[0], "echo", 5) == 0)
		return (echo((char **)exec->content->data));
	if (ft_strncmp(exec->content->data[0], "export", 7) == 0)
		return (export((char **)exec->content->data, &shell->env));
	if (ft_strncmp(exec->content->data[0], "env", 4) == 0)
		return (env((char **)exec->content->data, shell->env));
	if (ft_strncmp(exec->content->data[0], "unset", 6) == 0)
		return (unset((char **)exec->content->data, &shell->env));
	if (ft_strncmp(exec->content->data[0], "pwd", 4) == 0)
		return (pwd((char **)exec->content->data));
	if (ft_strncmp(exec->content->data[0], "exit", 5) == 0)
		return (b_exit(exec, shell));
	if (DEBUG_MODE)
		ft_putendl_fd("==builtin not found==", 2);
	return (EXIT_FAILURE);
}
