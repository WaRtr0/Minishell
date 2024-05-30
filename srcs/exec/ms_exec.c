/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:55:16 by gcros             #+#    #+#             */
/*   Updated: 2024/05/30 03:43:44 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "put.h"
#include "put.h"
#include "conf.h"

static int	is_builtin(char *str);
int			ms_execsh(t_exec *exec, t_shell *shell);

int	ms_exec(t_exec *exec, t_shell *shell)
{
	int	ret;

	if (DEBUG_MODE)
		ft_putendl_fd("==exec==", 2);
	ret = ms_execsh(exec, shell);
	return (ret);
}

int	ms_execsh(t_exec *exec, t_shell *shell)
{
	if (is_builtin(exec->content->data[0]))
	{
		if (shell->in_pipe)
			return (ms_exec_builtin(exec, shell));
		else
			return (ms_run_builtin(exec, shell));
	}
	else
		return (ms_exec_bin(exec, shell));
	return (-1);
}

static int	is_builtin(char *str)
{
	if (DEBUG_MODE)
		printf("==%s==\n", str);
	if (ft_strncmp(str, "cd", 3) == 0
		|| ft_strncmp(str, "exit", 5) == 0
		|| ft_strncmp(str, "echo", 5) == 0
		|| ft_strncmp(str, "export", 7) == 0
		|| ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	return (0);
}
