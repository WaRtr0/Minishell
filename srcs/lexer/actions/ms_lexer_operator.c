/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:17:05 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 15:41:44 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

static void	ms_lexer_text(t_command *command, t_shell *shell, t_parser_str *str)
{
	ms_add_join(shell, -1);
	ms_add_str(shell, command, str);
	ms_commit_command_str(shell, command);
}

static void	ms_lexer_pipeline(t_command *command, t_shell *shell,
	t_prompt_s *status)
{
	t_command	*second_command;

	second_command = NULL;
	ms_lexer_heredoc_handle(shell, status);
	command = ms_free_command(command);
	if (ms_is_join(shell))
	{
		ms_exit_join(shell);
		command = ft_arr_pop(shell->cursor);
		if (command && command->type == CMD_JOIN_NO_PRINT)
			second_command = ft_arr_pop(shell->cursor);
	}
	else if (ms_get_cursor(shell)->type == CMD_PARENTHESIS)
		command = ft_arr_pop(shell->cursor);
	ms_add_pipeline(shell);
	if (second_command != NULL)
		ms_commit_command_any(shell, second_command);
	ms_commit_command_any(shell, command);
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
		if (ms_get_size(shell->cursor_array) > 0
			&& ms_get_parent(shell, 1) != NULL
			&& ms_get_parent(shell, 1)->type != CMD_PARENTHESIS)
			shell->cursor = ft_arr_pop(shell->cursor_array);
		ms_add_cursor(shell, new_command);
	}
}
