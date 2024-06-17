/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:49:48 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:17:26 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_command	*ms_get_parent(t_shell *shell, size_t parent)
{
	size_t	size_array;
	size_t	size_cursor;
	t_array	*tmp_array;

	if (shell->cursor_array == NULL || shell->cursor_array->data == NULL)
		return (NULL);
	size_array = ms_get_size(shell->cursor_array);
	if (size_array == 0 || parent == 0 || parent > size_array)
		return (NULL);
	tmp_array = (t_array *)shell->cursor_array->data[size_array - parent];
	if (tmp_array == NULL || tmp_array->data == NULL)
		return (NULL);
	size_cursor = ms_get_size(tmp_array);
	if (size_cursor == 0)
		return (NULL);
	return ((t_command *)(((t_array *)shell->cursor_array->data[
				size_array - parent])->data[size_cursor - 1]));
}
