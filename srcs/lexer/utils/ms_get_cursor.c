/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:47:53 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:49:29 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_command	*ms_get_cursor(t_shell *shell)
{
	if (((t_array *)shell->cursor)->size > 0)
	{
		return (
			(t_command *)(
			(t_array *)shell->cursor
		)->data[
					(
						(t_array *)shell->cursor
					)->size - 1
				]
		);
	}
	return (NULL);
}
