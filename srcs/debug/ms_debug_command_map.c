/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_command_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:41:05 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 20:41:31 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	ms_debug_command_map(t_array *array, void *(*f)(void *))
{
	ft_arr_map(array, (void *)f, 0);
}
