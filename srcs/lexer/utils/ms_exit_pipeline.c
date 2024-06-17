/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:46:34 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/14 00:15:23 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ms_exit_pipeline(t_shell *shell)
{
	if (ms_is_pipeline(shell) && ms_get_size(shell->cursor_array) > 0)
		shell->cursor = ft_arr_pop(shell->cursor_array);
}
