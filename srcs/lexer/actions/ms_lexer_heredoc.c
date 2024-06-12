/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:08:07 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/12 18:52:09 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdint.h>

void	ms_lexer_heredoc_handle(t_shell *shell, t_prompt_s *status)
{
	char		*limiter;
	char		*temp;
	t_command	*command;

	limiter = NULL;
	if (shell->cursor_array->size > 0 && ms_get_parent(shell, 2) != NULL
		&& ms_get_parent(shell, 2)->type == CMD_HEREDOC)
	{
		ms_exit_join(shell);
		while (((t_array *)ms_get_cursor(shell)->content.array)->size > 0)
		{
			command = ft_arr_shift(ms_get_cursor(shell)->content.array);

			if (limiter != NULL && command->type == CMD_TEXT)
			{
				temp = limiter;
				limiter = ft_strjoin(limiter, command->content.str);
				free(temp);
				free(command->content.str);
			}
			else
				limiter = command->content.str;
			free(command);
		}
		ft_arr_free(&ms_get_cursor(shell)->content.array, NULL);
		free(ms_get_cursor(shell));
		shell->cursor = ft_arr_pop(shell->cursor_array);
		ft_arr_free(&ms_get_cursor(shell)->content.array, NULL);
		ms_get_cursor(shell)->content.str = limiter;
		ms_lexer_heredoc(shell, status);
	}
}

void	ms_lexer_heredoc_add(t_shell *shell, t_prompt_s *status)
{
	t_command	*new_command;

	if (status->no_print)
		ms_add_join(shell, CMD_JOIN_NO_PRINT);
	else
		ms_add_join(shell, -1);
	status->heredoc = 1;
	new_command = ms_new_command(shell);
	ms_add_type(new_command, CMD_HEREDOC);
	new_command->content.array = ft_arr_new(10);
	ft_arr_append(shell->cursor_array, shell->cursor);
	shell->cursor = new_command->content.array;
	ft_arr_append(shell->cursor_array->data[shell->cursor_array->size - 1],
		new_command);
}

void	ms_lexer_heredoc(t_shell *shell, t_prompt_s *status)
{
	t_command	*new_command;

	new_command = ms_get_cursor(shell);

	if (ms_heredoc(shell, new_command->content.str, status) == 0)
		shell->prompt_listen = 0;
	ms_add_type(new_command, CMD_HEREDOC);
	ms_add_fd(new_command,
		(int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 2]);
	status->heredoc = 0;
}
