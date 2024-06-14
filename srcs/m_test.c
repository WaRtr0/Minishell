/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:05:29 by gcros             #+#    #+#             */
/*   Updated: 2024/06/14 14:04:48 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#undef malloc
#include <unistd.h>
#include <stdlib.h>
#include "put.h"
#include <time.h>

#define CUR_FAIL 5535 + 1000

void	*mtest(size_t size)
{
	static size_t	i;

	ft_putnbr_fd(i++, 2);
	ft_putendl_fd("", 2);
	if (i + 1 == CUR_FAIL)
		ft_putendl_fd("fuck", 2);
	if (i++ > CUR_FAIL)
	{
		return (NULL);
	}

	return (malloc(size));
}
