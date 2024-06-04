/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathexp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 02:14:24 by gcros             #+#    #+#             */
/*   Updated: 2024/06/04 13:03:10 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "str.h"

void	swap(char **p1, char **p2);
void	sort_files(char **strs);

char	*exp_get_files(char **strs, int dir)
{
	char	*str;
	char	*p;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	sort_files(strs);
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
		if (strs[i + 1])
		*(p++) = ' ';
	}
	*(p) = '\0';
	return (str);
}

void	swap(char **p1, char **p2)
{
	char	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	sort_files(char **strs)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (strs[i])
	{
		j = i;
		while (j > 0 && ft_strncmp(strs[j - 1], strs[j], -1) > 0)
		{
			swap(strs + j, strs + j - 1);
			j--;
		}
		i++;
	}
}
