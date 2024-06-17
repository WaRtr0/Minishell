/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:06:41 by gcros             #+#    #+#             */
/*   Updated: 2024/05/21 10:53:17 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "stdio.h"

int	pattern_match(char *pattern, char *str)
{
	if (*pattern || *str)
	{
		if (*pattern == '*')
		{
			pattern++;
			while (*str)
				if (pattern_match(pattern, str++) == 0)
					return (0);
			return (!(*pattern == *str));
		}
		else if (*pattern == *str)
			return (pattern_match(pattern + 1, str + 1));
		else
			return (1);
	}
	return (!(*pattern == *str));
}
