/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clear_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:46:30 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/24 16:37:18 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	*ms_clear_command(t_command *command)
{
	if (command != NULL)
	{
		if (command->content.str != NULL)
			free(command->content.str);
	}
	return (ms_free_command(command));
}
