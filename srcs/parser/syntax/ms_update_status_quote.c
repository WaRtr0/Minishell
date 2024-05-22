/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_status_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:01:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 00:02:41 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_update_status_quote(t_prompt_s *status, t_type type)
{
	if (type == E_SQUOTE && !status->dquote)
		status->squote++;
	if (type == E_DQUOTE && !status->squote)
		status->dquote++;
	if (status->squote + status->dquote > 1)
	{
		status->print = 1;
		status->operator = 0;
		status->chevron = 0;
		status->no_empty = 1;
		status->newline = 0;
	}
}
