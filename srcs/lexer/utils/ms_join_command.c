/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_join_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:27:14 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 22:33:16 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	ms_join_command(t_shell *shell, char *str)
{
	char	*last_command;

	if (!shell->command || !str)
	{
		shell->prompt_listen = 0;
		shell->error = 1;
	}
	else
	{
		last_command = shell->command;
		shell->command = ft_strjoin(shell->command, str);
		free(last_command);
		free(str);
		if (!shell->command)
		{
			shell->prompt_listen = 0;
			shell->error = 1;
		}
	}
}
