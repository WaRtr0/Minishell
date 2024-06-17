/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:35:55 by gcros             #+#    #+#             */
/*   Updated: 2024/06/13 23:46:04 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

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
