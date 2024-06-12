/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:17:05 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/12 14:18:33 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

static void	ms_lexer_text(t_command *command, t_shell *shell, t_parser_str *str)
{
	ms_add_join(shell, -1);
	ms_add_str(shell, command, str);
	ms_commit_command(shell, command);
}

static void	ms_lexer_pipeline(t_command *command, t_shell *shell,
	t_prompt_s *status)
{
	ms_lexer_heredoc_handle(shell, status);
	command = ms_free_command(command);
	if (ms_is_join(shell))
	{
		ms_exit_join(shell);
		command = ft_arr_pop(shell->cursor);
	}
	else if (ms_get_cursor(shell)->type == CMD_PARENTHESIS)
		command = ft_arr_pop(shell->cursor);
	ms_add_pipeline(shell);
	ms_commit_command(shell, command);
}

void	ms_lexer_operator(t_shell *shell, t_prompt_s *status, t_parser_str *str)
{
	t_command	*new_command;

	if (ms_reset_quote(status))
		ms_join_command(shell, ft_select_str(&str->str[str->index], str->len));
	ms_append_quote(shell);
	new_command = ms_new_command(shell);
	ms_add_type(new_command, ms_get_cmd(str->type, &str->str[str->index]));
	if (ms_get_command_type(new_command) == CMD_PIPE)
		ms_lexer_pipeline(new_command, shell, status);
	else if (ms_get_command_type(new_command) == CMD_TEXT)
		ms_lexer_text(new_command, shell, str);
	else
	{
		ms_lexer_heredoc_handle(shell, status);
		ms_exit_join(shell);
		ms_exit_pipeline(shell);
		new_command->content.array = ft_arr_new(10);
		if (shell->cursor_array->size > 0 && ms_get_parent(shell, 1) != NULL
			&& ms_get_parent(shell, 1)->type != CMD_PARENTHESIS)
			shell->cursor = ft_arr_pop(shell->cursor_array);
		ft_arr_append(shell->cursor_array, shell->cursor);
		shell->cursor = new_command->content.array;
		ft_arr_append(shell->cursor_array->data[shell->cursor_array->size - 1],
			new_command);
	}
}
