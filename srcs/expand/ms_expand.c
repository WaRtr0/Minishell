/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:50:37 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/12 17:16:05 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "expand.h"
#include "debug.h"

static void	process_command(t_command *command,
	t_array *new_array, t_shell *shell)
{
	if (command->type == CMD_TEXT)
		ms_handle_cmd_text(command, new_array);
	else if (command->type == CMD_EXPAND_QUOTE)
		ms_handle_cmd_expand_quote(command, new_array, shell);
	else if (command->type == CMD_EXPAND)
		ms_handle_cmd_expand(command, new_array, shell);
	else if (command->type == CMD_WILDCARD)
		ms_handle_cmd_wildcard(new_array);
	else if (command->type == CMD_EMPTY)
		ms_handle_cmd_empty(new_array);
	else if (command->type == CMD_HEREDOC)
		ms_append_new_command_int(new_array, CMD_HEREDOC, command->content.fd);
	else
		ms_append_new_command_str(new_array, command->type, NULL);
}

t_array	*ms_new_join(t_array *array, t_shell *shell)
{
	t_array	*new_array;
	size_t	i;

	new_array = ms_initialize_new_array(shell);
	if (new_array == NULL)
		return (NULL);
	i = 0;
	while (i < array->size && shell->error < 1)
	{
		process_command((t_command *)array->data[i], new_array, shell);
		i++;
	}
	ms_handle_cmd_empty(new_array);
	return (new_array);
}
