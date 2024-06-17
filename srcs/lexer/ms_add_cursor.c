/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:55:12 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 18:38:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "utils.h"

static void	free_all(t_shell *shell, t_command *command)
{
	ft_arr_free(&command->content.array, NULL);
	free(command);
	shell->error = 1;
	shell->prompt_listen = 0;
}

void	ms_add_cursor(t_shell *shell, t_command *command)
{
	if (command == NULL)
		return ;
	if (shell->cursor_array != NULL && shell->cursor != NULL)
	{
		command->content.array = ft_arr_new(10);
		if (command->content.array == NULL)
			return (free_all(shell, command));
		if (ft_arr_append(shell->cursor, command) == 0)
			return (free_all(shell, command));
		if (ft_arr_append(shell->cursor_array, shell->cursor) == 0)
		{
			ft_arr_pop(shell->cursor);
			return (free_all(shell, command));
		}
		shell->cursor = command->content.array;
	}
}
