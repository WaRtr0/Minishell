/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/06/15 14:23:23 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "exec.h"
#include "minishell.h"
#include "prompt.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	(void) envp;
	ms_set_status(0);
	ft_bzero(&shell, sizeof(t_shell));
	ms_env_gen(envp, &(shell.env));
	ms_env_complete(&shell.env, argv[0]);
	ms_prompt(&shell);
	ms_env_collapse(&shell.env);
	return (ms_get_status());
}