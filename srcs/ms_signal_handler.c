/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:34:28 by gcros             #+#    #+#             */
/*   Updated: 2024/05/28 18:13:05 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE

#include <signal.h>
#include <stddef.h>
#include <readline/readline.h>
#include "put.h"
#include "exec.h"

void	do_nothing();
void	heredoc_handler();
void	prompt_handler();
void	quit_handler();

int	ms_sig_init(int rules)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	if (rules == 1 << 0)
		signal(SIGINT, prompt_handler);
	if (rules == 1 << 1)
		signal(SIGINT, heredoc_handler);
	return (0);
}

void	quit_handler()
{
}

void	heredoc_handler()
{
	ms_set_status(130);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(0);
}

void	prompt_handler()
{
	ms_set_status(130);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ms_sig_init(1 << 0);
}

void	do_nothing()
{
}