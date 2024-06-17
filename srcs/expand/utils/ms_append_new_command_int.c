/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_append_new_command_int.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 07:18:33 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 19:07:37 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "utils.h"

void	ms_append_new_command_int(t_array *new_array, int type, int content)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return ;
	new_command->content.fd = content;
	new_command->type = type;
	if (ft_arr_append(new_array, new_command) == 0)
		free(new_command);
}
