/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:08:07 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 22:14:06 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdint.h>

void	ms_lexer_heredoc(t_shell *shell, t_prompt_s *status)
{
	t_command	*new_command;

	if (status->no_print)
		ms_add_join(shell, CMD_JOIN_NO_PRINT);
	else
		ms_add_join(shell, -1);
	new_command = ms_new_command(shell);
	ms_add_type(new_command, CMD_HEREDOC);
	ms_add_fd(new_command,
		(int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 2]);
	ms_commit_command(shell, new_command);
	status->heredoc = 0;
}
