/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:53 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/11 17:35:22 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "conf.h"
#include "arr.h"
#include "lexer.h"
#include <sys/stat.h>
#include "env.h"
#include "exec.h"
#include "utils.h"
#include "handle.h"

#include "expand.h"

int add_exec_heredoc(t_exec *exec, t_command *command)
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

char *command_get_path(t_array *array, size_t *i, t_shell *shell)
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
		if (command->type == CMD_EMPTY && count > 0)
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

int add_exec_redir(t_exec *exec, t_array *array, size_t *i, t_shell *shell)
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
//new



//new
static int	run_join(t_array *array, t_exec *exec_cmd,
	t_shell *shell)
{
	size_t		i;
	t_command	*command;

	i = 0;
	command_get_redir(array, exec_cmd, shell);
	while (i < array->size && shell->error < 1)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT || command->type == CMD_EXPAND_QUOTE
			|| command->type == CMD_EXPAND)
			ft_arr_append(exec_cmd->content, command->content.str);
		i++;
	}
	return (0);
}



int	add_exec(t_exec **exec_cmd, t_shell *shell)
{
	*exec_cmd = malloc(sizeof(t_exec));
	if (exec_cmd == NULL)
	{
		shell->error = 1;
		return (shell->prompt_listen = 0);
	}
	(*exec_cmd)->content = ft_arr_new(20);
	(*exec_cmd)->redir = ft_arr_new(20);
	if ((*exec_cmd)->content == NULL || (*exec_cmd)->redir == NULL)
	{
		free(*exec_cmd);
		exec_cmd = NULL;
		shell->error = 1;
		return (shell->prompt_listen = 0);
	}
	(*exec_cmd)->fd[0] = -1;
	(*exec_cmd)->fd[1] = -1;
	return (1);
}
#include "expand.h"

int	ms_handle_join(t_array *array, t_shell *shell, int fd[2])
{
	t_exec		*exec_cmd;
	t_array		*new_array;

	if (!shell->prompt_listen || g_signal_value != 0)
	{
		return (0);
	}
	if (add_exec(&exec_cmd, shell) == 0 || exec_cmd == NULL)
		return (0);
	(void)array;
	new_array = ms_new_join(array, shell);
	if (new_array != NULL && new_array->size > 0) 
	{
		run_join(new_array, exec_cmd, shell);
		ft_arr_free(&new_array, free);
	}
	exec_cmd->fd[0] = fd[0];
	exec_cmd->fd[1] = fd[1];
	if (exec_cmd->content->size > 0 || exec_cmd->redir->size > 0)
		ms_set_status(ms_exec(exec_cmd, shell));
	ms_close_fd(fd, exec_cmd->fd);
	if (DEBUG_MODE == 1)
	{
		// ms_debug_command_to_json_exec(0, new_array);
		// printf("DEBUG MODE | REDIR\n");
		// ms_debug_command_to_json_exec(0, exec_cmd->redir);
	}
	free_exec(exec_cmd);
	return (1);
}