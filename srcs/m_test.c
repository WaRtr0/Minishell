/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:05:29 by gcros             #+#    #+#             */
/*   Updated: 2024/06/13 22:36:50 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#undef malloc
#include <unistd.h>
#include <stdlib.h>
#include "put.h"
#include <time.h>

#ifndef CUR_FAIL
# define CUR_FAIL 180
#endif

void	*mtest(size_t size)
{
	static size_t	i;

	if (i == 0)
		srand(time(NULL));
	// ft_putnbr_fd(i++, 2);
	// ft_putendl_fd("", 2);
	// if (i + 1 == CUR_FAIL)
	// 	ft_putendl_fd("fuck", 2);
	// if (i++ > CUR_FAIL)
	// {
	// 	return (NULL);
	// }
	i++;
	if ((rand() % 100) < 0)
	{
		ft_putendl_fd("FUCK", 2);
		return (NULL);
	}
	return (malloc(size));
}
