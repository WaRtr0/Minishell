/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_append_env_to_last_command.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:04:51 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 05:34:58 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "expand.h"

void ms_append_env_to_last_command(t_array *new_array, char *env_str)
{
	char *temp;

	temp = ms_get_last_command(new_array)->content.str;
	if (ms_get_last_type(new_array) == CMD_EXPAND && *ms_get_last_char(temp) == '$')
		*ms_get_last_char(temp) = '\0';
	ms_get_last_command(new_array)->content.str = ft_strjoin(temp, env_str);
	free(temp);
}