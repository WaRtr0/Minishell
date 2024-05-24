/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:53 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/24 16:00:56 by mmorot           ###   ########.fr       */
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

static int	add_word(t_command *command, char **word, t_shell *shell)
{
	char	*tmp;

	if (*word == NULL)
		*word = ft_strdup(command->content.str);
	else
	{
		tmp = *word;
		*word = ft_strjoin(*word, command->content.str);
		free(tmp);
	}
	if (*word == NULL)
	{
		shell->error = 1;
		shell->prompt_listen = 0;
		return (1);
	}
	return (0);
}

static int	commit_word(t_exec *exec_cmd, char **word)
{
	if (*word != NULL)
	{
		ft_arr_append(exec_cmd->content, *word);
		*word = NULL;
	}
	return (0);
}

static int	run_join(t_array *array, t_exec *exec_cmd,
	t_shell *shell, char **word)
{
	size_t		i;
	t_command	*command;

	i = 0;
	while (i < array->size && shell->error < 1)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT)
			add_word(command, word, shell);
		else if (command->type == CMD_EXPAND
			|| command->type == CMD_EXPAND_QUOTE)
			ms_expand(command, shell, exec_cmd, word);
		else if (command->type == CMD_EMPTY)
			commit_word(exec_cmd, word);
		else if (command->type == CMD_HEREDOC)
			ms_heredoc_part(array, &i, exec_cmd->fd);
		else if (command->type == CMD_REDIR_IN)
			ms_redir_in_part(array, &i, exec_cmd->fd);
		else if (command->type == CMD_REDIR_OUT)
			ms_redir_out_part(array, &i, exec_cmd->fd);
		else if (command->type == CMD_APPEND)
			ms_append_part(array, &i, exec_cmd->fd);
		i++;
	}
	return (0);
}

static int	add_exec(t_exec **exec_cmd, t_shell *shell)
{
	*exec_cmd = malloc(sizeof(t_exec));
	if (exec_cmd == NULL)
	{
		shell->error = 1;
		return (shell->prompt_listen = 0);
	}
	(*exec_cmd)->content = ft_arr_new(20);
	if ((*exec_cmd)->content == NULL)
	{
		free((*exec_cmd));
		shell->error = 1;
		return (shell->prompt_listen = 0);
	}
	(*exec_cmd)->fd[0] = -1;
	(*exec_cmd)->fd[1] = -1;
	return (1);
}

int	ms_handle_join(t_array *array, t_shell *shell, int fd[2])
{
	t_exec		*exec_cmd;
	char		*word;

	if (!shell->prompt_listen)
		return (0);
	add_exec(&exec_cmd, shell);
	word = NULL;
	if (exec_cmd == NULL)
		return (0);
	run_join(array, exec_cmd, shell, &word);
	if (exec_cmd->fd[0] == -1)
		exec_cmd->fd[0] = fd[0];
	if (exec_cmd->fd[1] == -1)
		exec_cmd->fd[1] = fd[1];
	if (word != NULL)
		ft_arr_append(exec_cmd->content, word);
	if (exec_cmd->content->size > 0)
		ms_exec(exec_cmd, shell);
	ms_close_fd(fd, exec_cmd->fd);
	free_exec(exec_cmd);
	return (1);
}
