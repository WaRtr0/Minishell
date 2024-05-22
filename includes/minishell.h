/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:19:27 by wartro            #+#    #+#             */
/*   Updated: 2024/05/22 21:01:44 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>

// libft
# include "char.h"
# include "str.h"
# include "arr.h"
# include "env.h"

typedef struct s_shell
{
	int		prompt_listen;
	int		line;
	int		status;
	int		error;
	int		arb_pipe;
	int		in_pipe;
	char	*prompt;
	t_array	*commands;
	t_array	*cursor_array;
	void	*cursor;
	char	*command;
	t_array	*heredoc_fd;
	int		heredoc_size;
	char	*limiter;
	t_env	*env;
}	t_shell;

union u_content
{
	char	*str;
	t_array	*array;
	int		fd;
};

typedef struct exec
{
	t_array	*content;
	int		fd[2];
}	t_exec;

int		main(int argc, char **argv, char **envp);
void	free_shell(t_shell *shell);

void	free_exec(t_exec *exec);

void	ms_get_fd(t_array *array, t_shell *shell, int *fd);

#endif