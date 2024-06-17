/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:34:28 by gcros             #+#    #+#             */
/*   Updated: 2024/06/11 20:59:33 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stddef.h>
#include <readline/readline.h>
#include "put.h"
#include "exec.h"

int		g_signal_value;

void	heredoc_handler(int signo, siginfo_t *info, void *context);
void	prompt_handler(int signo, siginfo_t *info, void *context);
void	quit_handler(int signo, siginfo_t *info, void *context);
void	exec_handler(int signo, siginfo_t *info, void *context);

int	ms_sig_set(enum e_sig_set rules)
{
	struct sigaction	act_int;

	ft_bzero(&act_int, sizeof(act_int));
	act_int.sa_flags = SA_SIGINFO | SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	if (rules == sig_restore)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		return (0);
	}
	else if (rules == sig_prompt)
		act_int.sa_sigaction = &prompt_handler;
	else if (rules == sig_heredoc)
		act_int.sa_sigaction = &heredoc_handler;
	else if (rules == sig_exec)
		act_int.sa_sigaction = &exec_handler;
	sigaction(SIGINT, &act_int, NULL);
	return (0);
}

void	quit_handler(int signo, siginfo_t *info, void *context)
{
	(void) signo;
	(void) info;
	(void) context;
}

void	heredoc_handler(int signo, siginfo_t *info, void *context)
{
	(void) signo;
	(void) info;
	(void) context;
	ms_set_status(signo);
	g_signal_value = signo;
	ft_putendl_fd("", 2);
	rl_replace_line("", 0);
	close(0);
}

void	prompt_handler(int signo, siginfo_t *info, void *context)
{
	(void) signo;
	(void) info;
	(void) context;
	ms_set_status(signo);
	ft_putendl_fd("", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	exec_handler(int signo, siginfo_t *info, void *context)
{
	(void) signo;
	(void) info;
	(void) context;
	g_signal_value = signo;
	rl_replace_line("", 0);
}
