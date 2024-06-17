/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd_expand_quote.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:39:14 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 23:39:31 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "expand.h"

void	ms_handle_cmd_expand_quote(t_command *command,
	t_array *new_array, t_shell *shell)
{
	char	*env_str;

	if (command == NULL || command->content.str == NULL)
		return ;
	if (command->content.str[0] == '\0')
	{
		if (ms_is_last_type_text_or_expand(new_array))
			ms_update_last_command_type(new_array, CMD_EXPAND_QUOTE, "$");
		else
			ms_append_new_command_str(new_array, CMD_EXPAND_QUOTE, "$");
	}
	else
	{
		env_str = ms_get_exp(command->content.str, shell->env);
		if (env_str == NULL)
			return ;
		if (ms_is_last_type_text_or_expand(new_array))
			ms_append_env_to_last_command(new_array, env_str);
		else
			ms_append_new_command_str(new_array, CMD_TEXT, env_str);
		free(env_str);
	}
}
