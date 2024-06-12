/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:52:29 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/12 14:49:06 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static int	add_exec_heredoc(t_exec *exec, t_command *command)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (1);
	new_command->type = CMD_HEREDOC;
	new_command->content.fd = command->content.fd;
	if (ft_arr_append(exec->redir, new_command) == 0)
	{
		free(new_command);
		return (1);
	}
	command->type = CMD_EMPTY;
	return (0);
}

static char	*command_get_path(t_array *array, size_t *i, t_shell *shell)
{
	t_command	*command;
	char		*path;
	int			count;

	count = 0;
	path = NULL;
	*i += 1;
	while (*i < array->size && shell->error < 1)
	{
		command = (t_command *)array->data[*i];
		if (command->type != CMD_TEXT && count > 0)
			return (path);
		else if (command->type == CMD_TEXT || command->type == CMD_EXPAND
			|| command->type == CMD_EXPAND_QUOTE)
		{
			path = command->content.str;
			command->type = CMD_EMPTY;
			command->content.str = NULL;
		}
		*i += 1;
		count++;
	}
	*i -= 1;
	return (path);
}

static int	add_exec_redir(t_exec *exec,
		t_array *array, size_t *i, t_shell *shell)
{
	t_command	*command;
	t_command	*new_command;
	char		*path;

	command = (t_command *)array->data[*i];
	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (1);
	new_command->type = command->type;
	path = command_get_path(array, i, shell);
	if (path == NULL)
	{
		free(new_command);
		return (1);
	}
	new_command->content.str = path;
	if (ft_arr_append(exec->redir, new_command) == 0)
	{
		free(new_command);
		return (1);
	}
	command->type = CMD_EMPTY;
	return (0);
}

int	command_get_redir(t_array *array, t_exec *exec_cmd, t_shell *shell)
{
	size_t		i;
	t_command	*command;

	i = 0;
	while (i < array->size && shell->error < 1)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_HEREDOC)
		{
			add_exec_heredoc(exec_cmd, command);
		}
		else if (command->type >= CMD_REDIR_IN && command->type <= CMD_APPEND)
			add_exec_redir(exec_cmd, array, &i, shell);
		i++;
	}
	return (0);
}
