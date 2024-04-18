/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:19:27 by wartro            #+#    #+#             */
/*   Updated: 2024/04/18 13:16:37 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#  define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

// libft
# include "char.h"
# include "str.h"
#include "arr.h"
# include "conf.h"


typedef struct s_shell
{
    int     prompt_listen;
    int     line;
    char    *prompt;
    t_array *commands;
    t_array *cursor_array;
    void    *cursor;
    char    *command;
    t_array *heredoc_fd;
    int     heredoc_size;
    char    *limiter;
}	t_shell;

int main(int argc, char **argv, char **envp);

#endif