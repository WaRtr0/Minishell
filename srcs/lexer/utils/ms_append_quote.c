/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_append_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:18 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/05 15:59:00 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ms_append_quote(t_shell *shell)
{
	t_command	*append_command;

	if (shell->command != NULL)
	{
		append_command = ms_new_command(shell);
		ms_add_type(append_command, CMD_TEXT);
		if (append_command)
			append_command->content.str = shell->command;
		ms_commit_command(shell, append_command);
		shell->command = NULL;
	}
}
