/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:40:22 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 08:50:03 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard.h"
#include "expand.h"

static void	apply_wildcard(t_array *new_array)
{
	t_array		*tmp_array;
	t_command	*command;
	char		*tmp_str;

	command = ft_arr_pop(new_array);
	tmp_array = ms_pathexp(command->content.str);
	free(command->content.str);
	free(command);
	if (tmp_array == NULL)
		return ;
	if (tmp_array->size > 1 &&
		(ms_get_before_type_widlcard(new_array) == CMD_REDIR_IN
			|| ms_get_before_type_widlcard(new_array) == CMD_REDIR_OUT
			|| ms_get_before_type_widlcard(new_array) == CMD_APPEND))
		printf("minishell: ambiguous redirect\n");
	while (tmp_array->size > 0)
	{
		tmp_str = ft_arr_shift(tmp_array);
		ms_append_new_command_str(new_array, CMD_TEXT, tmp_str);
		free(tmp_str);
		ms_append_new_command_str(new_array, CMD_EMPTY, NULL);
	}
	ft_arr_free(&tmp_array, NULL);
	return ;
}

void	ms_handle_cmd_empty(t_array *new_array)
{
	if (ms_get_last_type(new_array) == CMD_WILDCARD)
		apply_wildcard(new_array);
	else
		ms_append_new_command_str(new_array, CMD_EMPTY, NULL);
}
