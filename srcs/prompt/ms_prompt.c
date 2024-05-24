/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/24 17:48:20 by mmorot           ###   ########.fr       */
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

static	void	ms_prompt_init(t_shell *shell)
{
	shell->line = 0;
	shell->status = 0;
	shell->arb_pipe = 0;
	shell->in_pipe = 0;
}

static	int	ms_prompt_handle(t_shell *shell, char *line)
{
	t_prompt_s	status;

	status = (t_prompt_s){0};
	shell->heredoc_fd = ft_arr_new(10);
	shell->heredoc_size = 0;
	shell->commands = ft_arr_new(10);
	shell->cursor = shell->commands;
	shell->cursor_array = ft_arr_new(10);
	if (!line)
		return (1);
	if (line[0] != '\0')
	{
		// add_history(line);
		shell->prompt_listen = 0;
		status = (t_prompt_s){0};
		shell->prompt = ft_strdup(line);
		ms_parser(line, &status, shell);
		if (shell->prompt_listen)
			ms_handle(shell->commands, shell, (int [2]){0, 1});
		if (DEBUG_MODE)
			ms_debug(shell);
		free_shell(shell);
		shell->line++;
	}
	return (0);
}

int	ms_prompt(t_shell *shell)
{
	char			*line;

	ms_prompt_init(shell);
	// while (1)
	// {
		// line = readline(MS_NAME"$ ");
		// line = ft_strdup("&& hola tout le monde");
		line = ft_strdup("(a.out ah hello | a.out ah hello)");
		// line = ft_strdup("hola tout le monde");
		if (!ms_prompt_handle(shell, line))
			free(line);
	// }
	return (0);
}
