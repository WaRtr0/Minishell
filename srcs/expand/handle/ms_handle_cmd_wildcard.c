/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd_wildcard.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:19:40 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 07:17:21 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "expand.h"

void	ms_handle_cmd_wildcard(t_array *new_array)
{
	if (ms_is_last_type_text_or_expand(new_array))
		ms_update_last_command_type(new_array, CMD_WILDCARD, "*");
	else
		ms_append_new_command_str(new_array, CMD_WILDCARD, "*");
}
