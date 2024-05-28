/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:05:26 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/28 16:28:58 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	free_commands(t_array *array)
{
	size_t		i;
	t_command	*command;

	i = 0;

	if (!array)
		return (1);
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT || command->type == CMD_EXPAND
			|| command->type == CMD_QUOTE || command->type == CMD_EXPAND_QUOTE)
			free(command->content.str);
		else if (command->type == CMD_HEREDOC || command->type == CMD_EMPTY
			|| command->type == CMD_REDIR_IN || command->type == CMD_REDIR_OUT
			|| command->type == CMD_APPEND)
			(void)"tkt frere";
		else
			free_commands(command->content.array);
		free(command);
		i++;
	}
	ft_arr_free(&array, NULL);
	return (0);
}

void	free_prompt(t_shell *shell)
{
	ft_arr_free(&shell->cursor_array, NULL);
	ft_arr_free(&shell->heredoc_fd, NULL);
	free_commands(shell->commands);
	shell->cursor = NULL;
	free(shell->prompt);
}

void	free_shell(t_shell *shell)
{
	free_prompt(shell);
	ms_env_collapse(&shell->env);
}

void	free_exec(t_exec	*exec)
{
	ft_arr_free(&exec->content, free);
	free(exec);
}
