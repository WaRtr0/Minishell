/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/05/28 17:48:05 by gcros            ###   ########.fr       */
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
	(void) envp;
	ft_bzero(&shell, sizeof(t_shell));
	ms_env_gen(envp, &(shell.env));
	ms_env_complete(&shell.env, argv[0]);
	ms_prompt(&shell);
	ms_env_collapse(&shell.env);
	return (ms_get_status());
}

//#include "wildcard.h"
//#include <sys/types.h>
//#include <dirent.h>

//int	main(int ac, char **av)
//{
//	(void) ac;
//	(void) av;
//	char	*str;

//	if (ac != 2)
//		return (1);
//	str = ms_pathexp(av[1]);
//	printf("> %s\n", str);
//	free(str);
//	return (0);
//}

//#include "wildcard.h"

//int	main(int ac, char **av)
//{
//	if (ac != 3)
//		return (1);
//	printf("match : %d\n", pattern_match(av[1], av[2]));
//	return (0);
//}
