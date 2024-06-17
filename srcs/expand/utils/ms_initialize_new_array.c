/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_initialize_new_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:48:11 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 04:49:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array	*ms_initialize_new_array(t_shell *shell)
{
	t_array	*new_array;

	new_array = ft_arr_new(20);
	if (new_array == NULL)
	{
		shell->error = 1;
		shell->prompt_listen = 0;
	}
	return (new_array);
}
