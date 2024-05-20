/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:29:39 by gcros             #+#    #+#             */
/*   Updated: 2024/05/20 14:54:54 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arr.h"

void	free_shell(t_shell *shell)
{
	(void) shell;
}

void	free_exec(t_exec	*exec)
{
	ft_arr_free(&exec->content, free);
}
