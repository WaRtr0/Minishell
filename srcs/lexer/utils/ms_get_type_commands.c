/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_type_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:07:37 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 18:55:00 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ms_get_type_commands(t_command *command)
{
	if (command == NULL)
		return (0);
	if (command->type == CMD_TEXT || command->type == CMD_EXPAND
		|| command->type == CMD_QUOTE || command->type == CMD_EXPAND_QUOTE)
		return (1);
	if (command->type == CMD_HEREDOC || command->type == CMD_EMPTY
		|| command->type == CMD_REDIR_IN || command->type == CMD_REDIR_OUT
		|| command->type == CMD_APPEND || command->type == CMD_WILDCARD)
		return (0);
	return (2);
}
