/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:42:12 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/03 16:14:12 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "str.h"
#include <stdint.h>
#include <fcntl.h>
#include "exec.h"
#include <errno.h>

static int	add_fd(t_shell *shell)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		shell->prompt_listen = 0;
		shell->error = 2;
		return (1);
	}
	if (!ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fd[0]))
	{
		shell->prompt_listen = 0;
		shell->error = 1;
		return (1);
	}
	if (!ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fd[1]))
	{
		shell->prompt_listen = 0;
		shell->error = 1;
		return (1);
	}
	shell->heredoc_size += 2;
	return (0);
}

static	int	ms_heredoc_handle(t_shell *shell, char *line)
{
	if (line == NULL)
	{
		shell->prompt_listen = 0;
		return (0);
	}
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
	int		fds[2];

	save_io((int [2]){0, 1}, fds);
	ms_sig_set(sig_heredoc);
	shell->limiter = limiter;
	if (add_fd(shell))
	{
		free(limiter);
		return (0);
	}
	errno = 0;
	while (1)
	{
		newline = readline("heredoc> ");
		if (ms_heredoc_handle(shell, newline) == 0)
			break ;
	}
	restore_io(fds);
	write((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1],
		"\0", 1);
	close((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1]);
	free(limiter);
	ms_sig_set(sig_exec);
	return (errno == 0);
}
