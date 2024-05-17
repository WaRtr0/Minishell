#ifndef HANDLE_H
#  define HANDLE_H

# include "minishell.h"


void	ms_get_fd(t_array *array, t_shell *shell,int *fd);

int	ms_handle_join(t_array *array, t_shell *shell, int fd[2]);
int ms_handle_pipe(t_array *array, t_shell *shell, int fd[2]);
int ms_handle(t_array *array, t_shell *shell, int fd[2]);


#endif