/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_last_type_text_or_expand.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:10:20 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 06:41:23 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "expand.h"

int	ms_is_last_type_text_or_expand(t_array *new_array)
{
	int	last_type;

	last_type = ms_get_last_type(new_array);
	return (last_type == CMD_TEXT || last_type == CMD_EXPAND_QUOTE
		|| last_type == CMD_EXPAND || last_type == CMD_WILDCARD);
}
