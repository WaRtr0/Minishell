/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:54:00 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/21 00:04:12 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "arr.h"
#include "lexer.h"
#include "handle.h"

static	int	handle_pa(t_array *array, t_shell *shell, int fd[2], size_t i)
{
	int			t_fd[2];
	t_command	*command;
	t_command	*second_command;

	t_fd[0] = fd[0];
	t_fd[1] = fd[1];
	command = (t_command *)array->data[i];
	if (i + 1 < array->size)
	{
		second_command = (t_command *)array->data[i + 1];
		if (second_command->type == CMD_JOIN_NO_PRINT)
		{
			ms_get_fd(second_command->content.array, shell, t_fd);
		}
	}
	ms_handle(command->content.array, shell, t_fd);
	return (1);
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
			ms_handle_join(command->content.array, shell, fd);
		else if (command->type == CMD_AND_IF && !shell->status)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_OR && shell->status)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_SEMICOLON)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_PIPE)
			ms_handle_pipe(command->content.array, shell, fd);
		else if (command->type == CMD_PARENTHESIS)
			handle_pa(array, shell, fd, i);
		i++;
	}
	return (1);
}
