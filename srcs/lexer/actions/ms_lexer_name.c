/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:58:56 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 22:05:33 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ms_lexer_name(t_shell *shell, t_prompt_s *status, t_parser_str *str)
{
	t_command	*new_command;

	ms_add_join(shell, -1);
	ms_append_quote(shell);
	new_command = ms_new_command(shell);
	ms_add_type(new_command, CMD_EXPAND);
	if (status->dquote)
		ms_add_type(new_command, CMD_EXPAND_QUOTE);
	if (status->squote)
	{
		ms_add_type(new_command, CMD_TEXT);
		ms_add_str(shell, new_command, str);
	}
	else
	{
		str->index++;
		str->len--;
		ms_add_str(shell, new_command, str);
	}
	ms_commit_command(shell, new_command);
}
