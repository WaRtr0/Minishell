/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:26 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:15:06 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ms_exit_join(t_shell *shell)
{
	if (ms_is_join(shell) && ms_get_size(shell->cursor_array) > 0)
		shell->cursor = ft_arr_pop(shell->cursor_array);
}
