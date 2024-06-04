/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:19:27 by wartro            #+#    #+#             */
/*   Updated: 2024/06/04 12:40:03 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# include <signal.h>
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
	int		last_pid;
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

enum e_sig_set
{
	sig_restore = 0,
	sig_prompt = 1 << 0,
	sig_heredoc = 1 << 1,
	sig_exec = 1 << 2,
};

extern int	g_signal_value;

//int	main(int argc, char **argv, char **envp);
char	*next_line(char *prompt);

void	free_shell(t_shell *shell);
void	free_prompt(t_shell *shell);
void	free_exec(t_exec *exec);
int		ms_sig_set(enum e_sig_set rules);
void	ms_get_fd(t_array *array, t_shell *shell, int *fd);

int		ms_exit_status(int new_status, int save);
void	ms_set_status(int new_status);
int		ms_get_status(void);

#endif