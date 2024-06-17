/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_before_type_widlcard.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:43:13 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:36:44 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_command_type	ms_get_before_type_widlcard(t_array *array)
{
	int			i;
	t_command	*command;

	i = ms_get_size(array) - 1;
	while (i >= 0)
	{
		command = (t_command *)array->data[i];
		if (command && command->type != CMD_EMPTY
			&& command->type != CMD_WILDCARD)
			return (command->type);
		i--;
	}
	return (0);
}
