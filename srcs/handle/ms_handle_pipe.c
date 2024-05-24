/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:56 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/24 20:44:35 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "conf.h"
#include "arr.h"
#include "lexer.h"
#include "utils.h"
#include "env.h"
#include "exec.h"
#include "handle.h"

static	int	join_part(t_array *array, t_shell *shell, int fd[2])
{
	shell->in_pipe = 1;
	return (ms_handle_join(array, shell, fd));
}

static	int	pare_part(t_array *array, t_shell *shell, int fd[2], size_t i)
{
	int			t_fd[2];
	pid_t		pid;
	t_command	*command;
	t_command	*second_command;

	t_fd[0] = fd[0];
	t_fd[1] = fd[1];
	command = (t_command *)array->data[i];
	if (i + 1 < array->size)
	{
		second_command = (t_command *)array->data[i + 1];
		if (second_command->type == CMD_JOIN_NO_PRINT)
			ms_get_fd(second_command->content.array, shell, t_fd);
	}
	pid = fork();
	if (pid == 0)
		exit(ms_handle(command->content.array, shell,
				(int [2]){t_fd[0], t_fd[1]}));
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	ms_close_fd(fd, t_fd);
	return (0);
}

static	int	pipe_input(t_pipe_run *run)
{
	if (run->index < run->array->size - 1)
	{
		//close(run->pipe_fd[0]);
		if (pipe(run->pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		run->tmp_fd[1] = run->pipe_fd[1];
	}
	else
	{
		run->tmp_fd[1] = run->fd[1];
	}
	return (0);
}

static	int	pipe_run(t_pipe_run *run, t_shell *shell)
{
	t_command	*command;

	command = (t_command *)run->array->data[run->index];
	pipe_input(run);
	if (command->type == CMD_JOIN)
		join_part(command->content.array, shell,
			(int [2]){run->tmp_fd[0], run->tmp_fd[1]});
	else if (command->type == CMD_PARENTHESIS)
		pare_part(run->array, shell,
			(int [2]){run->tmp_fd[0], run->tmp_fd[1]}, run->index);
	if (run->index < run->array->size - 1)
	{
		close(run->pipe_fd[1]);
		run->tmp_fd[0] = run->pipe_fd[0];
	}
	run->index++;
	return (0);
}

int	ms_handle_pipe(t_array *array, t_shell *shell, int fd[2])
{
	t_pipe_run	run;

	run.tmp_fd[0] = fd[0];
	run.fd[0] = fd[0];
	run.fd[1] = fd[1];
	run.array = array;
	shell->arb_pipe++;
	if (!shell->prompt_listen)
		return (0);
	run.index = 0;
	while (run.index < array->size)
		pipe_run(&run, shell);
	while (wait(NULL) != -1)
		(void) "todo";
	shell->in_pipe--;
	return (0);
}
