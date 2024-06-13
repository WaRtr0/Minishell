/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:49:52 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 16:54:08 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	ms_lexer_wildcard(t_shell *shell, t_parser_str *str)
{
	t_command	*new_command;

	(void)str;
	ms_add_join(shell, -1);
	new_command = ms_new_command(shell);
	ms_add_type(new_command, CMD_WILDCARD);
	ms_commit_command_fd(shell, new_command);
}
