/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:20:52 by gcros             #+#    #+#             */
/*   Updated: 2024/04/10 05:31:47 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

/**
 * @brief create new t_env
 * 
 * @param key string used as key 
 * @param value string used as stored value
 * @return  a malloc t_env or NULL if failed
 */
t_env	*ms_env_new(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env != NULL)
		ms_env_init(key, value, env);
	return (env);
}
