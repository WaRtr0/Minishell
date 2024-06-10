/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_last_command_type.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:11:56 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 06:48:01 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "expand.h"

void	ms_update_last_command_type(t_array *new_array, int type, char *suffix) {
	char *temp;

	temp = ms_get_last_command(new_array)->content.str;
	if (ms_get_last_type(new_array) == CMD_EXPAND && *ms_get_last_char(temp) == '$')
		*ms_get_last_char(temp) = '\0';
	if (ms_get_last_type(new_array) == CMD_WILDCARD)
		type = CMD_WILDCARD;
	ms_get_last_command(new_array)->type = type;
	ms_get_last_command(new_array)->content.str = ft_strjoin(temp, suffix);
	free(temp);
}
