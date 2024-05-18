/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_seperator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 05:29:24 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/18 05:30:12 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin_seperator(char *s1, char *s2, char *sep)
{
	size_t	l;
	char	*ptr;

	l = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep) + 1;
	ptr = malloc(l);
	if (!ptr)
		return (ptr);
	ft_strlcpy(ptr, s1, l);
	ft_strlcat(ptr, sep, l);
	ft_strlcat(ptr, s2, l);
	return (ptr);
}
