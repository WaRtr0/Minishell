/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_status_operator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:59:25 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 00:00:53 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_update_status_operator(t_prompt_s *status, t_type type,
		t_parser_str *str)
{
	if (type > E_PARENTHESIS && type <= E_OPERATOR)
	{
		status->newline = 0;
		status->c_parenthesis = 0;
		status->print = 0;
		if (ms_is_chevron(type))
			status->chevron = 1;
		else
		{
			if (type == E_OPERATOR)
				status->newline = 1;
			else if (type == E_METACHAR && ft_strncmp(&str->str[str->index],
					"|", 1) == 0)
				status->newline = 1;
			status->operator = 1;
			status->no_print = 0;
		}
	}
}
