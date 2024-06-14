/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:05:26 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 22:35:11 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	free_commands(t_array *array)
{
	size_t		i;
	int			type;
	t_command	*command;

	i = 0;
	if (array == NULL || array->data == NULL)
		return (1);
	while (i < array->size && array->data[i] != NULL)
	{
		command = (t_command *)array->data[i];
		if (command == NULL)
		{
			i++;
			continue ;
		}
		type = ms_get_type_commands(command);
		if (type == 1)
			free(command->content.str);
		else if (type == 2)
			free_commands(command->content.array);
		free(command);
		i++;
	}
	ft_arr_free(&array, NULL);
	return (0);
}

void	free_prompt(t_shell *shell)
{
	if (shell->cursor_array)
		ft_arr_free(&shell->cursor_array, NULL);
	else
		free(shell->cursor_array);
	if (shell->heredoc_fd)
		ft_arr_free(&shell->heredoc_fd, NULL);
	else
		free(shell->heredoc_fd);
	if (shell->commands)
		free_commands(shell->commands);
	else
		free(shell->commands);
	free(shell->command);
	free(shell->prompt);
	shell->command = NULL;
	shell->cursor = NULL;
	shell->cursor_array = NULL;
	shell->heredoc_fd = NULL;
	shell->commands = NULL;
	shell->prompt = NULL;
}

void	free_shell(t_shell *shell)
{
	free_prompt(shell);
	ms_env_collapse(&shell->env);
}

static void	redir_free(t_command *command)
{
	if (command && command->type != CMD_HEREDOC)
		free(command->content.str);
	free(command);
}

void	free_exec(t_exec	*exec)
{
	ft_arr_free(&exec->redir, (void *)(void *)redir_free);
	ft_arr_free(&exec->content, free);
	free(exec);
}
