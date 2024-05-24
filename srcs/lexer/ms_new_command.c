/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_new_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:45:48 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 20:55:41 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_command	*ms_new_command(t_shell *shell)
{
	t_command	*new_command;

	new_command = (t_command *)malloc(sizeof(t_command));
	if (new_command == NULL)
	{
		shell->error = 1;
		shell->prompt_listen = 0;
	}
	return (new_command);
}
