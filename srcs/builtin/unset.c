/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:12:57 by gcros             #+#    #+#             */
/*   Updated: 2024/06/06 12:52:50 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <unistd.h>
#include <stdlib.h>

int	unset(char **av, t_env **env)
{
	char	**ptr;

	ptr = av;
	while (*++ptr)
		ms_env_remove(env, *ptr);
	return (EXIT_SUCCESS << 8);
}

