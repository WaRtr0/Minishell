/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_metachar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:43:39 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:43:40 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "parser.h"


int	ms_get_metachar(char *str)
{
	if (!ft_strncmp(str, S_AND, ft_strlen(S_AND)))
		return (E_AND);
	if (!ft_strncmp(str, S_PIPE, ft_strlen(S_PIPE)))
		return (E_PIPE);
	if (!ft_strncmp(str, S_SEMICOLON, ft_strlen(S_SEMICOLON)))
		return (E_SEMICOLON);
	return (-1);
}
