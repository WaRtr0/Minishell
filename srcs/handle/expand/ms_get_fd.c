/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:50:18 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/31 15:35:58 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <sys/stat.h>

int	ms_heredoc_part(t_array *array, size_t *i, int *t_fd)
{
	t_command	*command;

	command = (t_command *)array->data[(*i)];
	if (t_fd[0] != -1)
		close(t_fd[0]);
	t_fd[0] = command->content.fd;
	return (1);
}

int	ms_redir_in_part(t_array *array, size_t *i, int *t_fd)
{
	t_command	*command;

	if (t_fd[0] != -1)
		close(t_fd[0]);
	(*i)++;
	command = (t_command *)array->data[(*i)];
	if (command->type == CMD_EMPTY)
		(*i)++;
	command = (t_command *)array->data[(*i)];
	t_fd[0] = open(command->content.str, O_RDONLY);
	return (1);
}

int	ms_append_part(t_array *array, size_t *i, int *t_fd)
{
	t_command	*command;

	if (t_fd[1] != -1)
		close(t_fd[1]);
	(*i)++;
	command = (t_command *)array->data[(*i)];
	if (command->type == CMD_EMPTY)
		(*i)++;
	command = (t_command *)array->data[(*i)];
	t_fd[1] = open(command->content.str, O_CREAT | O_APPEND | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	return (1);
}

int	ms_redir_out_part(t_array *array, size_t *i, int *t_fd)
{
	t_command	*command;

	if (t_fd[1] != -1)
		close(t_fd[1]);
	(*i)++;
	command = (t_command *)array->data[(*i)];
	if (command->type == CMD_EMPTY)
		(*i)++;
	command = (t_command *)array->data[(*i)];
	t_fd[1] = open(command->content.str, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	return (1);
}

void	ms_get_fd(t_array *array, t_shell *shell, int *fd)
{
	t_command	*command;
	int			t_fd[2];
	size_t		i;

	(void)shell;
	t_fd[0] = -1;
	t_fd[1] = -1;
	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_HEREDOC)
			ms_heredoc_part(array, &i, t_fd);
		else if (command->type == CMD_REDIR_IN)
			ms_redir_in_part(array, &i, t_fd);
		else if (command->type == CMD_REDIR_OUT)
			ms_redir_out_part(array, &i, t_fd);
		else if (command->type == CMD_APPEND)
			ms_append_part(array, &i, t_fd);
		i++;
	}
	if (t_fd[0] != -1)
		fd[0] = t_fd[0];
	if (t_fd[1] != -1)
		fd[1] = t_fd[1];
}
