/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_status_text.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:56:27 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 23:57:52 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_update_status_text(t_prompt_s *status, t_type type)
{
	if (type == E_WORD || type == E_NAME)
	{
		status->print = 1;
		status->operator = 0;
		status->chevron = 0;
		status->newline = 0;
		status->no_empty = 1;
		status->c_parenthesis = 0;
	}
}
