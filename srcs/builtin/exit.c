/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:55:46 by gcros             #+#    #+#             */
/*   Updated: 2024/05/28 15:26:03 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "exec.h"
#include "put.h"
#include "num.h"

int	def_exit(t_exec *exec, t_shell *shell);
int	arg_exit(t_exec *exec, t_shell *shell);

int	b_exit(t_exec *exec, t_shell *shell)
{
	size_t	i;

	ft_putendl_fd("exit", 1);
	i = 3;
	while (i < 1024)
		close(i++);
	if (exec->content->size == 2)
		return (arg_exit(exec, shell));
	return (def_exit(exec, shell));
}

int	def_exit(t_exec *exec, t_shell *shell)
{
	free_shell(shell);
	free_exec(exec);
	exit(ms_get_status());
}

int	arg_exit(t_exec *exec, t_shell *shell)
{
	int	st;

	st = ft_atoi(exec->content->data[1]);
	free_shell(shell);
	free_exec(exec);
	exit(st);
}
