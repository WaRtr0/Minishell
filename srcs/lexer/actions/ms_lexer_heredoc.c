/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:08:07 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/05 13:15:05 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdint.h>

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
