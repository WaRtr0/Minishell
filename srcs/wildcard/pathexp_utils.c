/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathexp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:14:24 by gcros             #+#    #+#             */
/*   Updated: 2024/06/01 02:27:04 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exp_get_files(char **strs, int dir)
{
	char	*str;
	char	*p;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (strs[i])
		count += ft_strlen(strs[i++]);
	str = malloc(count + 1 + i + dir * count);
	if (!str)
		return (NULL);
	i = 0;
	p = str;
	while (strs[i])
	{
		p = ft_stpcpy(p, strs[i++]);
		if (dir)
			*(p++) = '/';
		*(p++) = ' ';
	}
	*(p) = '\0';
	return (str);
}
