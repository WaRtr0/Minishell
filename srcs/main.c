/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/05/23 00:36:43 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "ft_printf.h"
//#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "exec.h"
#include "minishell.h"
#include "prompt.h"

/**
 * @brief Fonction principale du programme qui va
 * initialiser la structure shell et lancer le prompt
 * 
 * @param argc
 * @param argv
 * @param envp
 * @return int **0** si tout c'est bien passé sinon **1**
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	ft_bzero(&shell, sizeof(t_shell));
	ms_env_gen(envp, &(shell.env));
	ms_env_complete(&shell.env, argv[0]);
	ms_prompt(&shell);
	return (0);
}
