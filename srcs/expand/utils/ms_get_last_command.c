/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_last_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:06:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 08:02:28 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_command	*ms_get_last_command(t_array *array)
{
	if (array->size > 0)
		return ((t_command *)array->data[array->size - 1]);
	return (NULL);
}
