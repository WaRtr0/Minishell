/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:09:43 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/17 11:34:35 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "handle.h"
#include "utils.h"

int	ms_wait_pipeline(t_shell *shell)
{
	int	pid;
	int	tmp_stat;
	int	exit_stat;

	pid = 0;
	exit_stat = ms_get_status() << 8;
	while (pid != -1)
	{
		pid = wait(&tmp_stat);
		if (pid == shell->last_pid)
			exit_stat = tmp_stat;
	}
	return (exit_stat);
}

int	exit_pare_part(t_command *command, t_shell *shell, int fds[2])
{
	int	i;

	ms_handle(command->content.array, shell, fds);
	free_shell(shell);
	i = 3;
	while (i < 1024)
		close(i++);
	exit(ms_get_status());
}
