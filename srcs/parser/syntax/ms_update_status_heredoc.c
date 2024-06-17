/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_status_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:58:22 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 23:58:42 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_update_status_heredoc(t_prompt_s *status, t_type type)
{
	if (type == E_HEREDOC)
	{
		status->heredoc = 1;
		status->no_empty = 1;
		status->print = 0;
	}
}
