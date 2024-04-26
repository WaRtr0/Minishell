/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_exist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:17:43 by gcros             #+#    #+#             */
/*   Updated: 2024/04/26 08:16:48 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief check if a value exist
 * 
 * @param env the env tree
 * @param key the key to search
 * @return 1 if the key is found, 0 else
 */
int	ms_env_exist(t_env *env, char *key)
{
	int	cmp;

	if (env == NULL)
		return (0);
	cmp = ft_strncmp(env->key, key, ft_strlen(key) + 1);
	if (cmp == 0)
		return (1);
	else if (cmp < 0)
		return (ms_env_exist(env->right, key));
	else
		return (ms_env_exist(env->left, key));
	return (0);
}
