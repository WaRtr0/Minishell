/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:47:53 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:20:43 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_command	*ms_get_cursor(t_shell *shell)
{
	if (shell->cursor == NULL || ((t_array *)shell->cursor)->data == NULL)
		return (NULL);
	if (ms_get_size(shell->cursor) > 0)
	{
		return (
			(t_command *)(
			(t_array *)shell->cursor
		)->data[
					ms_get_size(shell->cursor) - 1
				]
		);
	}
	return (NULL);
}
