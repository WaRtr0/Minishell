/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_last_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:06:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:36:35 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_command	*ms_get_last_command(t_array *array)
{
	t_command	*command;

	if (array != NULL && array->data != NULL && ms_get_size(array) > 0)
	{
		command = array->data[ms_get_size(array) - 1];
		if (command != NULL)
			return (command);
	}
	return (NULL);
}
