/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_cmd_to_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:43:41 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 20:43:49 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

char	*ms_debug_cmd_to_str(t_command_type type)
{
	static char	*cmd[] = {"CMD_PIPE", "CMD_REDIR_IN", "CMD_REDIR_OUT",
		"CMD_APPEND", "CMD_HEREDOC", "CMD_SEMICOLON", "CMD_AND_IF", "CMD_AND",
		"CMD_OR", "CMD_QUOTE", "CMD_PARENTHESIS", "CMD_EXPAND",
		"CMD_EXPAND_QUOTE", "CMD_TEXT", "CMD_JOIN", "CMD_JOIN_NO_PRINT",
		"CMD_EMPTY", "CMD_WILDCARD"};

	return (cmd[type]);
}
