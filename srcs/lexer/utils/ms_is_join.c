/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:50:59 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:15:57 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	ms_is_join(t_shell *shell)
{
	if (ms_get_size(shell->cursor_array) > 0 && ms_get_parent(shell, 1) != NULL
		&& (ms_get_parent(shell, 1)->type == CMD_JOIN
			|| ms_get_parent(shell, 1)->type == CMD_JOIN_NO_PRINT))
		return (1);
	return (0);
}
