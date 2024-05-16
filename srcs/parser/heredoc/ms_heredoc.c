#include "arr.h"
#include "char.h"
#include "conf.h"
#include "minishell.h"
#include "prompt.h"
#include "str.h"
// #include "num.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "exec.h"
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>


static int	add_fd(t_shell *shell)
{
	(void)shell;
	int		fd[2];
	// 0 = read
	// 1 = write

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

int ms_heredoc(t_shell *shell, char *limiter)
{
    char    *newline;

    shell->limiter = limiter;
    if (add_fd(shell))
        return (0);
    while (1)
    {
        newline = readline("heredoc> ");
        if (!newline)
            break ;
        if (ft_strlen(shell->limiter) == ft_strlen(newline) && ft_strncmp(newline, shell->limiter, ft_strlen(shell->limiter)) == 0)
        {
            free(newline);
            break ;
        }
        write(
            ((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1]), 
            newline, 
            ft_strlen(newline));
        write((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1], "\n", 1);
        free(newline);
    }
    write((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1], "\0", 1);
    close((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1]);
    //check
    return (1);
}