/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_print_json.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:42:02 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/31 18:06:43 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	*ms_debug_print_json(t_command *command)
{
	printf("{");
	printf("type:`%d-%s`,", command->type, ms_debug_cmd_to_str(command->type));
	if (command->type == CMD_TEXT || command->type == CMD_EXPAND
		|| command->type == CMD_EXPAND_QUOTE)
		printf("content:`%s`", command->content.str);
	else if (command->type == CMD_WILDCARD || command->type == CMD_EMPTY)
		(void)"void";
	else if (command->type == CMD_HEREDOC || command->type == CMD_REDIR_IN
		|| command->type == CMD_REDIR_OUT || command->type == CMD_APPEND)
		printf("content:%d", command->content.fd);
	else if (command->content.array != NULL)
	{
		printf("content:[");
		ms_debug_command_map(command->content.array,
			(void *)ms_debug_print_json);
		printf("],");
	}
	printf("},");
	return (command);
}
