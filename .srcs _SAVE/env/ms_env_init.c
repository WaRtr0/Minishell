/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:34:21 by gcros             #+#    #+#             */
/*   Updated: 2024/04/06 00:42:01 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/**
 * @brief init a t_env object
 * 
 * @param key string used as key 
 * @param value string used as value
 * @param *env the reference to t_env object
 */
void	ms_env_init(char *key, char *value, t_env *env)
{
	*env = (t_env){.key = key, .value = value, .left = NULL, .right = NULL};
}
