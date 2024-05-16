#ifndef LEXER_H
#  define LEXER_H

# include "minishell.h"


int	ms_handle_join(t_array *array, t_shell *shell, int fd[2]);
int ms_handle_pipe(t_array *array, t_shell *shell, int fd[2]);
int ms_handle(t_array *array, t_shell *shell, int fd[2]);


#endif