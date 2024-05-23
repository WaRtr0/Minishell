/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:07 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 22:21:36 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ms_add_pipeline(t_shell *shell)
{
	t_command	*append_command;

	if (!ms_is_pipeline(shell))
	{
		append_command = ms_new_command(shell);
		ms_add_type(append_command, CMD_PIPE);
		append_command->content.array = ft_arr_new(10);
		ms_commit_command(shell, append_command);
		ft_arr_append(shell->cursor_array, shell->cursor);
		shell->cursor = append_command->content.array;
	}
}
