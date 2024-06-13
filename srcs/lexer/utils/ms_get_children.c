/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:45 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:19:25 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_command	*ms_get_children(t_shell *shell, size_t children)
{
	size_t	size_array;
	size_t	size_cursor;
	t_array	*tmp_array;

	if (shell->cursor_array == NULL || shell->cursor_array->data == NULL)
		return (NULL);
	size_array = ms_get_size(shell->cursor_array);
	if (size_array == 0 || 1 > size_array)
		return (NULL);
	size_cursor = ms_get_size(shell->cursor_array->data[size_array - 1]);
	if (size_cursor == 0 || children <= 0 || children > size_cursor)
		return (NULL);
	tmp_array = (t_array *)shell->cursor_array->data[size_array - 1];
	if (tmp_array == NULL || tmp_array->data == NULL)
		return (NULL);
	return ((t_command *)(tmp_array->data[size_cursor - children]));
}
