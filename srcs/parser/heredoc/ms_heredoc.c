/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:42:12 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:42:19 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "str.h"
#include <stdint.h>
#include <fcntl.h>

static int	add_fd(t_shell *shell)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror(ERR_PIPE);
		return (1);
	}
	if (!ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fd[0]))
	{
		perror(ERR_MALLOC);
		return (1);
	}
	if (!ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fd[1]))
	{
		perror(ERR_MALLOC);
		return (1);
	}
	shell->heredoc_size += 2;
	return (0);
}

static	int	ms_heredoc_handle(t_shell *shell, char *line)
{
	if (!line)
		return (1);
	if (ft_strlen(shell->limiter) == ft_strlen(line)
		&& ft_strncmp(line, shell->limiter, ft_strlen(shell->limiter)) == 0)
	{
		free(line);
		return (0);
	}
	write(
		((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1]),
		line,
		ft_strlen(line));
	write((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1],
		"\n", 1);
	free(line);
	return (1);
}

int	ms_heredoc(t_shell *shell, char *limiter)
{
	char	*newline;

	shell->limiter = limiter;
	if (add_fd(shell))
		return (0);
	while (1)
	{
		newline = readline("heredoc> ");
		if (ms_heredoc_handle(shell, newline) == 0)
			break ;
	}
	write((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1],
		"\0", 1);
	close((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1]);
	return (1);
}
