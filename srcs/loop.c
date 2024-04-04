/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wartro <wartro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:28:53 by wartro            #+#    #+#             */
/*   Updated: 2024/04/04 20:53:12 by wartro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "prompt.h"

/**
 * @brief Un super main
 * 
 * @param ac Paramètre 1
 * @param av Paramètre 2
 * @param env 
 * @return int 
 */
int	loop(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	char **s;

	s = env;
	while (*s != NULL)
	{
		printf("%s\n", *s);
		s++;
	}
	return (0);
}
