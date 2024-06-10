/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:36:47 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 07:17:21 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "expand.h"

void	ms_handle_cmd_text(t_command *command, t_array *new_array) {
	char	*temp;

	if (ms_is_last_type_text_or_expand(new_array)) {
		temp = ms_get_last_command(new_array)->content.str;
		if (ms_get_last_type(new_array) == CMD_EXPAND && *ms_get_last_char(temp) == '$')
			*ms_get_last_char(temp) = '\0';
		if (ms_get_last_type(new_array) != CMD_WILDCARD)
			ms_get_last_command(new_array)->type = CMD_TEXT;
		ms_get_last_command(new_array)->content.str = ft_strjoin(temp, command->content.str);
		free(temp);
	} else {
		ms_append_new_command_str(new_array, CMD_TEXT, command->content.str);
	}
}