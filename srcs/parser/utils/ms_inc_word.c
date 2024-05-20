/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_inc_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:19 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:44:19 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "utils.h"

int ms_inc_word(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_include(NO_WORD, str[i]))
		i++;
	return (i);
}
