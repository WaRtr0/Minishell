/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:54:00 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/24 15:59:47 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arr.h"
#include "lexer.h"
#include "handle.h"

static	int	classic_part(t_array *array, t_shell *shell, int fd[2])
{
	return (ms_handle(array, shell, fd));
}

static	int	join_part(t_array *array, t_shell *shell, int fd[2])
{
	return (ms_handle_join(array, shell, fd));
}

static	int	pipe_part(t_array *array, t_shell *shell, int fd[2])
{
	return (ms_handle_pipe(array, shell, fd));
}

static	int	pare_part(t_array *array, t_shell *shell, int fd[2], size_t i)
{
	int			t_fd[2];
	t_command	*command;
	t_command	*second_command;
	int			response;

	t_fd[0] = fd[0];
	t_fd[1] = fd[1];
	command = (t_command *)array->data[i];
	if (i + 1 < array->size)
	{
		second_command = (t_command *)array->data[i + 1];
		if (second_command->type == CMD_JOIN_NO_PRINT)
			ms_get_fd(second_command->content.array, shell, t_fd);
	}
	response = ms_handle(command->content.array, shell, t_fd);
	ms_close_fd(fd, t_fd);
	return (response);
}

int	ms_handle(t_array *array, t_shell *shell, int fd[2])
{
	size_t		i;
	t_command	*command;

	if (!shell->prompt_listen)
		return (0);
	shell->in_pipe = 0;
	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_JOIN)
			join_part(command->content.array, shell, fd);
		else if (command->type == CMD_AND_IF && !shell->status)
			classic_part(command->content.array, shell, fd);
		else if (command->type == CMD_OR && shell->status)
			classic_part(command->content.array, shell, fd);
		else if (command->type == CMD_SEMICOLON)
			classic_part(command->content.array, shell, fd);
		else if (command->type == CMD_PIPE)
			pipe_part(command->content.array, shell, fd);
		else if (command->type == CMD_PARENTHESIS)
			pare_part(array, shell, fd, i);
		i++;
	}
	return (1);
}
