/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_join_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:57:55 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 23:06:48 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	ms_join_prompt(t_shell *shell, char *str, char *sep)
{
	if (!shell->prompt || !str)
	{
		shell->prompt_listen = 0;
		shell->error = 1;
	}
	else
	{
		shell->prompt = ft_strjoin_seperator(shell->prompt, str, sep);
		if (!shell->prompt)
		{
			shell->prompt_listen = 0;
			shell->error = 1;
		}
	}
}
