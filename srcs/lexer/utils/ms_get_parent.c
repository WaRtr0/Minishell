/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:49:48 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:50:47 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_command	*ms_get_parent(t_shell *shell, size_t parent)
{
	size_t	size_array;
	size_t	size_cursor;

	size_array = shell->cursor_array->size;
	if (size_array == 0 || parent == 0 || parent > size_array)
		return (NULL);
	size_cursor = ((t_array *)shell->cursor_array->data[
			size_array - parent])->size;
	if (size_cursor == 0)
		return (NULL);
	return ((t_command *)(((t_array *)shell->cursor_array->data[
				size_array - parent])->data[size_cursor - 1]));
}
