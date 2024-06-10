/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_last_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:17:33 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 08:02:23 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_command_type	ms_get_last_type(t_array *array)
{
	if (array->size > 0)
		return (((t_command *)array->data[array->size - 1])->type);
	return (CMD_EMPTY);
}
