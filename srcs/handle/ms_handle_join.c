/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:53 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/11 23:45:13 by gcros            ###   ########.fr       */
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

static int	add_exec(t_exec **exec_cmd, t_shell *shell)
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
	if (shell->prompt_listen && (exec_cmd->content->size > 0 || exec_cmd->redir->size > 0))
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
