/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:09:43 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/21 18:46:46 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "handle.h"
#include "utils.h"
#include "exec.h"

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
	ms_handle(command->content.array, shell, fds);
	free_shell(shell);
	close_all();
	exit(ms_get_status());
}
