/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:55:46 by gcros             #+#    #+#             */
/*   Updated: 2024/05/22 19:40:59 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "exec.h"
#include "put.h"

int	def_exit(t_exec *exec, t_shell *shell);
int	ag_exit(t_exec *exec, t_shell *shell);

int	b_exit(t_exec *exec, t_shell *shell)
{
	ft_putendl_fd("exit", 1);
	if (exec->content->size == 2)
		return (ag_exit(exec, shell));
	return (def_exit(exec, shell));
}

int	def_exit(t_exec *exec, t_shell *shell)
{
	int	st;

	st = shell->status;
	free_shell(shell);
	free_exec(exec);
	ft_putnbr_fd(st, 2);
	exit(st - 1);
}

int	ag_exit(t_exec *exec, t_shell *shell)
{
	int	st;

	st = atoi(exec->content->data[1]);
	free_shell(shell);
	free_exec(exec);
	ft_putnbr_fd(st, 2);
	exit(st);
}
