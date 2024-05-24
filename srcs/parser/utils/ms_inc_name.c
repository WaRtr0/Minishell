/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_inc_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:10 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:44:10 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "utils.h"

int	ms_inc_name(const char *str)
{
	size_t	i;

	i = 1;
	if (str[i] && str[i] == '?')
		return (2);
	while (str[i] && (ft_isdigit(str[i])
			|| ft_isalpha(str[i])
			|| ft_include("_", str[i])))
		i++;
	return (i);
}
