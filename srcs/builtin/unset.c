/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:12:57 by gcros             #+#    #+#             */
/*   Updated: 2024/06/11 20:55:08 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <unistd.h>
#include <stdlib.h>
#include "put.h"

int	unset(char **av, t_env **env)
{
	char	**ptr;

	if (av[1] && av[1][0] == '-')
	{
		ft_putendl_fd("mishell: unset: no flags allowed", 2);
		return (2 << 8);
	}
	ptr = av;
	while (*++ptr)
		ms_env_remove(env, *ptr);
	return (EXIT_SUCCESS << 8);
}
