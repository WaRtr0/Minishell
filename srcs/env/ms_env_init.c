/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:34:21 by gcros             #+#    #+#             */
/*   Updated: 2024/06/13 23:46:10 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	ms_env_init(char *key, char *value, t_env *env)
{
	*env = (t_env){.key = key, .value = value, .left = NULL, .right = NULL};
}
