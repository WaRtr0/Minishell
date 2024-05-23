/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:39:22 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 20:47:02 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	print_heredoc_fd(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->heredoc_size > 0 && i <= shell->heredoc_size / 2)
	{
		printf(C_BLUE"- FD: %d | %d\n"C_RESET,
			(int)(intptr_t)shell->heredoc_fd->data[i],
			(int)(intptr_t)shell->heredoc_fd->data[i + 1]);
		i += 2;
	}
}

static void	print_heredoc_content(t_shell *shell)
{
	int		i;
	char	*buffer;

	i = 0;
	while (shell->heredoc_size > 0 && i < shell->heredoc_size)
	{
		buffer = ft_calloc(sizeof(char), 10000);
		ft_strcpy(buffer, "test");
		read((int)(intptr_t)shell->heredoc_fd->data[i], buffer, 10000);
		printf(C_BLUE"%s\n"C_RESET, buffer);
		free(buffer);
		i += 2;
	}
}

int	ms_debug(t_shell *shell)
{
	printf(C_RED"%s\n"C_RESET, shell->prompt);
	printf(C_GREEN"FD: %d\n"C_RESET, shell->heredoc_size / 2);
	printf("--------------------\n"C_GREEN"[");
	ms_debug_command_map(shell->commands, (void *)ms_debug_print_json);
	printf("]"C_RESET"\n--------------------\n");
	ms_debug_command_to_json(0, shell->commands);
	print_heredoc_fd(shell);
	print_heredoc_content(shell);
	printf("\n--------------------\n");
	return (0);
}
