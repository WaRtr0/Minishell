/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:37:21 by gcros             #+#    #+#             */
/*   Updated: 2024/05/03 00:08:04 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	const char	*bigref;

	bigref = big;
	if (*little == '\0')
		return ((char *)big);
	if (*bigref == '\0' || ft_strlen(bigref) < ft_strlen(little))
		return (NULL);
	while (*bigref)
	{
		i = 0;
		while (bigref[i] == little[i] && little[i] && (bigref - big + i) < len)
			i++;
		if (little[i] == '\0')
			return ((char *)bigref);
		bigref++;
	}
	return (NULL);
}
