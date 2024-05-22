/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:26:27 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 21:39:06 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	ms_lexer_redir(t_shell *shell, t_prompt_s *status, t_parser_str *str)
{
	t_command	*new_command;

	if (status->no_print)
		ms_add_join(shell, CMD_JOIN_NO_PRINT);
	else
		ms_add_join(shell, -1);
	new_command = ms_new_command(shell);
	ms_add_type(new_command, ms_get_cmd(str->type, &str->str[str->index]));
	ms_add_fd(new_command, 0);
	ms_commit_command(shell, new_command);
}
