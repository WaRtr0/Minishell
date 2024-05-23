/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/24 00:26:57 by mmorot           ###   ########.fr       */
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

static int free_commands(t_array *array)
{
	size_t	i;
	t_command	*command;

	i = 0;

	if (!array)
		return (1);
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		printf("command->type: %d\n", command->type);
		if (command->type == CMD_TEXT || command->type == CMD_EXPAND || command->type == CMD_QUOTE || command->type == CMD_EXPAND_QUOTE)
			free(command->content.str);
		else if (command->type == CMD_HEREDOC || command->type == CMD_EMPTY || command->type == CMD_REDIR_IN || command->type == CMD_REDIR_OUT || command->type == CMD_APPEND)
			(void)"tkt frere";
		else
			free_commands(command->content.array);
		free(command);
		i++;
	}
	ft_arr_free(&array, NULL);
	return (0);
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
		shell->line++;
		//Free
		ft_arr_free(&shell->cursor_array, NULL);
		ft_arr_free(&shell->heredoc_fd, free); // A check
		free_commands(shell->commands);
		shell->cursor = NULL;
		free(shell->prompt);
		//endFree
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
		line = ft_strdup("echo coucou && echo salut > test");
		// line = ft_strdup("hola tout le monde");
		if (!ms_prompt_handle(shell, line))
			free(line);
	// }
	return (0);
}
