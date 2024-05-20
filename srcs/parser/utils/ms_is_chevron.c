/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:23 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:44:29 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "parser.h"

int	ms_is_chevron(t_type type)
{
	if (type == E_REDIR_IN
		|| type == E_REDIR_OUT
		|| type == E_APPEND
		|| type == E_HEREDOC)
		return (1);
	return (0);
}
