/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wartro <wartro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:37:28 by gcros             #+#    #+#             */
/*   Updated: 2024/04/04 19:55:17 by wartro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


int	main(int ac, char **av, char **env)
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
