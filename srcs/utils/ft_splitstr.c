/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 05:30:21 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/18 05:30:25 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_countwords_char(char const *str, char *sep)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_include(sep, *str))
			str++;
		if (*str && !ft_include(sep, *str))
			count++;
		while (*str && !ft_include(sep, *str))
			str ++;
	}
	return (count);
}

static char	*ft_getnextword_char(char const *str, char *sep)
{
	char	*buf;
	size_t	i;

	while (*str && ft_include(sep, *str))
		str++;
	i = 0;
	while (str[i] && !ft_include(sep, str[i]))
		i++;
	buf = (char *) malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && !ft_include(sep, str[i]) && buf)
	{
		buf[i] = str[i];
		i++;
	}
	if (buf)
		buf[i] = '\0';
	return (buf);
}

static void	ft_freebuf(char ***buf)
{
	ft_strsfree(buf[0]);
	buf[0] = NULL;
}

char	**ft_split_chars(char const *s, char *c)
{
	size_t		count;
	char		**buf;
	size_t		i;
	char const	*str;

	str = s;
	count = ft_countwords_char(str, c);
	buf = (char **) malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count && buf)
	{
		buf[i] = ft_getnextword_char(str, c);
		if (!buf[i])
			ft_freebuf(&buf);
		while (*str && ft_include(c,*str))
			str++;
		while (*str && !ft_include(c,*str))
			str++;
		i++;
	}
	if (buf)
		buf[count] = NULL;
	return (buf);
}
