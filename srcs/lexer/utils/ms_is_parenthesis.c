/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:46:05 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 23:46:09 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ms_is_parenthesis(t_shell *shell)
{
	if (shell->cursor_array->size > 0 && ms_get_parent(shell, 1) != NULL
		&& ms_get_parent(shell, 1)->type == CMD_PARENTHESIS)
		return (1);
	return (0);
}
