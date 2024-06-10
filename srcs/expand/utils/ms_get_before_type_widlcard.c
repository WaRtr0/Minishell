/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_before_type_widlcard.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:43:13 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 08:53:37 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_command_type	ms_get_before_type_widlcard(t_array *array)
{
	int			i;
	t_command	*command;

	i = array->size - 1;
	while (i >= 0)
	{
		command = (t_command *)array->data[i];
		if (command->type != CMD_EMPTY && command->type != CMD_WILDCARD)
			return (command->type);
		i--;
	}
	return (0);
}
