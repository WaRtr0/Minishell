/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:51:47 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:52:02 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	ms_is_pipeline(t_shell *shell)
{
	if (shell->cursor_array->size > 0 && ms_get_parent(shell, 1) != NULL
		&& ms_get_parent(shell, 1)->type == CMD_PIPE)
		return (1);
	return (0);
}
