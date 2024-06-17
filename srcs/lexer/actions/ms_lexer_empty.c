/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:20:35 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 17:00:27 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ms_lexer_empty(t_shell *shell, t_prompt_s *status)
{
	t_command	*new_command;

	if (ms_is_join(shell))
		ms_lexer_heredoc_handle(shell, status);
	if (ms_is_join(shell))
	{
		new_command = ms_new_command(shell);
		ms_add_type(new_command, CMD_EMPTY);
		ms_commit_command_fd(shell, new_command);
	}
}
