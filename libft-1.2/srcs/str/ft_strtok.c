/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:07:18 by gcros             #+#    #+#             */
/*   Updated: 2024/04/19 20:40:49 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strtok(char *str, char *charset)
{
	static char	*save;

	if (str != NULL)
		save = str;
	if (save == NULL || *save == '\0')
		return (NULL);
	while (*save && ft_strchr(charset, *save) != NULL)
		save++;
	str = save;
	while (*save && ft_strchr(charset, *save) == NULL)
		save++;
	if (str == save)
		return (NULL);
	if (*save == '\0')
		return (str);
	*save = '\0';
	save++;
	return (str);
}
