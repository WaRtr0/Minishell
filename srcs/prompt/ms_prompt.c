/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/18 05:51:23 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ms_prompt.c
 * @brief Fichier qui contient la fonction qui va lancer le prompt
 *
 */

#include "conf.h"
#include "minishell.h"
#include "parser.h"
#include "handle.h"


int	ms_prompt(t_shell *shell)
{
	char			*line;
	t_prompt_s		status;

	shell->line = 0;
	shell->status = 0;
	shell->arb_pipe = 0;
	shell->in_pipe = 0;
	while (1)
	{
		status = (t_prompt_s){0};
		line = readline(MS_NAME"$ ");
		shell->heredoc_fd = ft_arr_new(10);
		shell->heredoc_size = 0;
		shell->commands = ft_arr_new(10);
		shell->cursor = shell->commands;
		shell->cursor_array = ft_arr_new(10);
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			shell->prompt_listen = 0;
			status = (t_prompt_s){0};
			shell->prompt = ft_strdup(line);
			ms_parser(line, &status, shell);
			if (shell->prompt_listen)
				ms_handle(shell->commands, shell, (int [2]){0, 1});
			if (DEBUG_MODE)
				ms_debug(shell);
			shell->line++;
		}
		free(line);
	}
	return (0);
}
