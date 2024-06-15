/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:55:16 by gcros             #+#    #+#             */
/*   Updated: 2024/06/15 14:22:01 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "put.h"
#include "conf.h"

static int	is_builtin(char *str);
int			ms_execsh(t_exec *exec, t_shell *shell);

int	ms_exec(t_exec *exec, t_shell *shell)
{
	int	ret;

	if (DEBUG_MODE)
		ft_putendl_fd("==exec==", 2);
	ret = get_redir(exec) << 8;
	if (ret == 0)
		ret = ms_execsh(exec, shell);
	close(exec->dfl_fds[0]);
	close(exec->dfl_fds[1]);
	return (ret);
}

int	ms_execsh(t_exec *exec, t_shell *shell)
{
	if (exec->content->size == 0)
		return (0);
	if (ft_strncmp(exec->content->data[0], ".", -1) == 0)
	{
		ft_putendl_fd(MS_NAME": .: Is a directory", 2);
		return (127 << 8);
	}
	if (ft_strncmp(exec->content->data[0], "..", -1) == 0)
	{
		ft_putendl_fd(MS_NAME": ..: Is a directory", 2);
		return (127 << 8);
	}
	if (is_builtin(exec->content->data[0]))
	{
		if (shell->in_pipe)
			return (ms_exec_builtin(exec, shell));
		else
			return (ms_run_builtin(exec, shell));
	}
	else
		return (ms_exec_bin(exec, shell));
	return (141 << 8);
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
