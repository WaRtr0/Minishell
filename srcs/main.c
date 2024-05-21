/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/05/21 15:37:24 by gcros            ###   ########.fr       */
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

/**
 * @file main.c
 * @brief Fichier principale du programme qui va initialiser la structure shell et lancer le prompt
 * 
 */
 
#include "minishell.h"
#include "prompt.h"

/**
 * @brief Fonction principale du programme qui va initialiser la structure shell et lancer le prompt
 * 
 * @param argc **Non Utilisé** (Argument Count) Contient le nombre d'arguments passés au programme
 * @param argv **Non Utilisé** (Argument Vector) Contient les arguments passés au programme
 * @param envp Variable d'**environnement** qui seront **dupliqué** et **stocké** dans la **structure shell**
 * @return int **0** si tout c'est bien passé sinon **1**
 */
int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	ms_sig_init();
	ms_env_gen(envp, &(shell.env));
	ms_env_complete(&shell.env, argv[0]);
	ms_prompt(&shell);
	ms_env_collapse(&shell.env);
	return (0);
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
