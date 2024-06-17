/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cursor_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:47:06 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/22 23:48:48 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ms_get_cursor_type(t_shell *shell)
{
	if (ms_get_cursor(shell) != NULL)
		return (ms_get_cursor(shell)->type);
	return (-1);
}
