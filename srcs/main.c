/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wartro <wartro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:10:41 by wartro            #+#    #+#             */
/*   Updated: 2024/04/05 00:16:39 by wartro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	// a replace
	(void) envp; // traiter par gcros
	t_shell	*shell;
	shell = malloc(sizeof(t_shell) * 1);
	if (!shell)
		return (1);
	// !a replace

	ms_prompt(shell);

	return (0);
}
