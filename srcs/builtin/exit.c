/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:55:46 by gcros             #+#    #+#             */
/*   Updated: 2024/05/31 18:26:29 by gcros            ###   ########.fr       */
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
	if (exec->content->size == 1)
		return (def_exit(exec, shell));
	else
		return (arg_exit(exec, shell));
	return (EXIT_FAILURE);
}

int	exit_error(int err, char *op)
{
	char	*err_msg;

	err_msg = NULL;
	if (err == 0)
		err_msg = ft_strsjoin((char *[])
			{"mishell: exit: too many argument", NULL});
	else if (err == 1)
		err_msg = ft_strsjoin((char *[])
			{"mishell: exit: ", op, ": bad arguments", NULL});
	else
		err_msg = ft_strdup("mishell: exit: good luck");
	if (err_msg)
		ft_putendl_fd(err_msg, 2);
	free(err_msg);
	return (err);
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
	if (!ft_strisnumber(exec->content->data[1]))
	{
		if (exit_error(1, exec->content->data[1]) == 1)
			st = 2;
	}
	else if (exec->content->size > 2)
	{
		if (exit_error(0, NULL) == 0)
			return (EXIT_FAILURE);
	}
	free_shell(shell);
	free_exec(exec);
	exit(st);
}
