/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_inc_blank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:01 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:44:02 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "utils.h"

int	ms_inc_blank(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_include(BLANK, str[i]))
		i++;
	return (i);
}
