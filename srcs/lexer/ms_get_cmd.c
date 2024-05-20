/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:05 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:52:08 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

t_command_type	ms_get_cmd(int type, char *str)
{
	if (type == E_OPERATOR)
	{
		if (ms_get_operator(str) == E_OR)
			return (CMD_OR);
		if (ms_get_operator(str) == E_AND_IF)
			return (CMD_AND_IF);
	}
	if (type == E_METACHAR)
	{
		if (ms_get_metachar(str) == E_AND)
			return (CMD_AND);
		if (ms_get_metachar(str) == E_PIPE)
			return (CMD_PIPE);
		if (ms_get_metachar(str) == E_SEMICOLON)
			return (CMD_SEMICOLON);
	}
	if (type == E_REDIR_IN)
		return (CMD_REDIR_IN);
	if (type == E_REDIR_OUT)
		return (CMD_REDIR_OUT);
	if (type == E_APPEND)
		return (CMD_APPEND);
	return (CMD_TEXT);
}
