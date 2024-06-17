/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commit_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:44:03 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 17:08:20 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	ms_commit_command_str(t_shell *shell, t_command *command)
{
	if (command != NULL && shell->cursor != NULL)
	{
		if (ft_arr_append(shell->cursor, command) == 0)
		{
			free(command->content.str);
			free(command);
			shell->error = 1;
			shell->prompt_listen = 0;
		}
	}
}

void	ms_commit_command_fd(t_shell *shell, t_command *command)
{
	if (command != NULL && shell->cursor != NULL)
	{
		if (ft_arr_append(shell->cursor, command) == 0)
		{
			free(command);
			shell->error = 1;
			shell->prompt_listen = 0;
		}
	}
}

void	ms_commit_command_array(t_shell *shell, t_command *command)
{
	if (command != NULL && shell->cursor != NULL)
	{
		if (ft_arr_append(shell->cursor, command) == 0)
		{
			free_commands(command->content.array);
			free(command);
			shell->error = 1;
			shell->prompt_listen = 0;
		}
	}
}

void	ms_commit_command_any(t_shell *shell, t_command *command)
{
	int	type;

	if (command != NULL && shell->cursor != NULL)
	{
		if (ft_arr_append(shell->cursor, command) == 0)
		{
			type = ms_get_type_commands(command);
			if (type == 1)
				free(command->content.str);
			else if (type == 2)
				free_commands(command->content.array);
			free(command);
			shell->error = 1;
			shell->prompt_listen = 0;
		}
	}
}
