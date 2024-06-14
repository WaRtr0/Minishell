/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_last_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:17:33 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:36:25 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_command_type	ms_get_last_type(t_array *array)
{
	t_command	*command;

	if (array != NULL && array->data != NULL && ms_get_size(array) > 0)
	{
		command = array->data[ms_get_size(array) - 1];
		if (command != NULL)
			return (command->type);
	}
	return (CMD_EMPTY);
}
