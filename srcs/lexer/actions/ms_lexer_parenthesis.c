/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_parenthesis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:01:16 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 23:46:46 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

static int	open_parenthesis(t_shell *shell, t_prompt_s *status,
	t_parser_str *str)
{
	t_command	*new_command;

	if (ms_is_pipeline(shell) && status->c_parenthesis
		&& ms_get_cursor_type(shell) == CMD_PARENTHESIS)
		return (ms_syntax_error(E_SYNTAX_UPD_TOK,
				ft_select_str(&str->str[str->index], str->len), shell));
	if (ms_is_join(shell))
		return (ms_syntax_error(E_SYNTAX_UPD_TOK,
				ft_select_str(&str->str[str->index], str->len), shell));
	if (ms_get_cursor_type(shell) == CMD_PARENTHESIS && !ms_is_pipeline(shell))
		return (ms_syntax_error(E_SYNTAX_UPD_TOK,
				ft_select_str(&str->str[str->index], str->len), shell));
	status->c_parenthesis = 0;
	status->parenthesis += 1;
	status->no_empty = 0;
	new_command = ms_new_command(shell);
	ms_add_type(new_command, CMD_PARENTHESIS);
	new_command->content.array = ft_arr_new(10);
	ft_arr_append(shell->cursor, new_command);
	ft_arr_append(shell->cursor_array, shell->cursor);
	shell->cursor = new_command->content.array;
	status->last_parenthesis = status->parenthesis;
	return (0);
}

static int	close_parenthesis(t_shell *shell, t_prompt_s *status,
	t_parser_str *str)
{
	status->c_parenthesis = 1;
	if ((status->parenthesis == 0 || status->operator || !status->no_empty)
		&& (ms_get_cursor_type(shell) != CMD_SEMICOLON))
		return (ms_syntax_error(E_SYNTAX_UPD_TOK,
				ft_select_str(&str->str[str->index], str->len), shell));
	else
	{
		ms_exit_join(shell);
		status->last_parenthesis = status->parenthesis;
		if (!ms_is_parenthesis(shell))
			shell->cursor = ft_arr_pop(shell->cursor_array);
		shell->cursor = ft_arr_pop(shell->cursor_array);
		status->parenthesis -= 1;
		status->no_print = 1;
	}
	return (0);
}

void	ms_lexer_parenthesis(t_shell *shell, t_prompt_s *status,
	t_parser_str *str)
{
	status->newline = 0;
	status->no_print = 0;
	if (ft_strncmp(&str->str[str->index], "(", 1) == 0)
		open_parenthesis(shell, status, str);
	else
		close_parenthesis(shell, status, str);
}
