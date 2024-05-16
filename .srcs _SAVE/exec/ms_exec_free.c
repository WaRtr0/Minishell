/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:29:39 by gcros             #+#    #+#             */
/*   Updated: 2024/05/07 01:31:27 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arr.h"

void    free_shell(t_shell *shell)
{
	(void) shell;
	
}

void    free_exec(t_exec    *exec)
{
	ft_arr_free(&exec->content, free);
}
