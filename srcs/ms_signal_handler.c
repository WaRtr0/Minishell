/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:34:28 by gcros             #+#    #+#             */
/*   Updated: 2024/05/16 21:52:59 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE

#include <signal.h>
#include <stddef.h>
#include <readline/readline.h>
#include "put.h"
#include "exec.h"

void	do_nothing();
void	int_handler();
void	quit_handler();

int	ms_sig_init()
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
	return (0);
}

void	quit_handler()
{
}

void	int_handler()
{
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ms_sig_init();
}

void	do_nothing()
{
}