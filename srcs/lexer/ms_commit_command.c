/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commit_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:44:03 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 20:45:15 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ms_commit_command(t_shell *shell, t_command *command)
{
	if (command != NULL && shell->cursor != NULL)
		ft_arr_append(shell->cursor, command);
}
