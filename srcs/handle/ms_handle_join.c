/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:53 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/21 19:09:49 by mmorot           ###   ########.fr       */
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

int	ms_handle_join(t_array *array, t_shell *shell, int fd[2])
{
	t_exec	    *exec_cmd;
	t_command	*command;
	char		*word;
	size_t	i;

	if (!shell->prompt_listen)
		return (0);
	exec_cmd = malloc(sizeof(t_exec));
	exec_cmd->content = ft_arr_new(20);
	exec_cmd->fd[0] = -1;
	exec_cmd->fd[1] = -1;

	word = NULL;
	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT)
		{
			if (!word)
				word = ft_strdup("");
			word = ft_strjoin(word, command->content.str);
		}
		else if (command->type == CMD_EXPAND || command->type == CMD_EXPAND_QUOTE)
		{
			ms_expand(command, shell, exec_cmd, word);
		}
		else if (command->type == CMD_EMPTY)
		{
			if (word != NULL)
				ft_arr_append(exec_cmd->content, word);
			word = NULL;
		}
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
	if (exec_cmd->fd[0] == -1)
		exec_cmd->fd[0] = fd[0];
	if (exec_cmd->fd[1] == -1)
		exec_cmd->fd[1] = fd[1];
	if (word != NULL)
		ft_arr_append(exec_cmd->content, word);
	if (exec_cmd->content->size > 0)
		ms_exec(exec_cmd, shell);
	return (1);
}
