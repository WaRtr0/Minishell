/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:35:55 by gcros             #+#    #+#             */
/*   Updated: 2024/04/10 18:46:29 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

/**
 * @brief search and return the value of a key
 * 
 * @param env the env tree
 * @param key the key to search
 * @return the value NULL if not set or not found
 */
char	*ms_env_get(t_env *env, char *key)
{
	int	cmp;

	if (env == NULL)
		return (NULL);
	cmp = ft_strncmp(env->key, key, ft_strlen(key) + 1);
	if (cmp == 0)
		return (env->value);
	else if (cmp < 0)
		return (ms_env_get(env->right, key));
	else
		return (ms_env_get(env->left, key));
	return (NULL);
}
