/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_append_new_command_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:06:39 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 19:07:25 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "utils.h"

void	ms_append_new_command_str(t_array *new_array, int type, char *content)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return ;
	new_command->content.str = NULL;
	if (type == CMD_EXPAND && ft_include(content, '*'))
		type = CMD_WILDCARD;
	if (content != NULL)
		new_command->content.str = ft_strdup(content);
	new_command->type = type;
	if (ft_arr_append(new_array, new_command) == 0)
	{
		free(new_command->content.str);
		free(new_command);
	}
}
