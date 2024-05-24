/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reset_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:48 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:44:58 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ms_reset_quote(t_prompt_s *status)
{
	if (status->squote + status->dquote > 1)
	{
		status->squote = 0;
		status->dquote = 0;
		return (1);
	}
	return (0);
}
