/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:01 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 20:12:18 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ms_add_join(t_shell *shell, int type )
{
	t_command	*append_command;

	if (!ms_is_join(shell))
	{
		append_command = ms_new_command(shell);
		ms_add_type(append_command, CMD_JOIN);
		if (type >= 0)
			ms_add_type(append_command, type);
		if (append_command == NULL)
			return ;
		append_command->content.array = ft_arr_new(10);
		if (append_command->content.array == NULL)
			return (free(append_command));
		ms_commit_command_array(shell, append_command);
		if (ft_arr_append(shell->cursor_array, shell->cursor))
			shell->cursor = append_command->content.array;
	}
}
