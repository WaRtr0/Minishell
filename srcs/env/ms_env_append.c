/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:21:14 by gcros             #+#    #+#             */
/*   Updated: 2024/04/23 22:30:04 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <unistd.h>

int	ms_env_append(t_env **env, char *key, char *value)
{
	char	*dup_key;
	char	*dup_value;
	t_env	*node;

	dup_key = ft_strdup(key);
	dup_value = NULL;
	if (value != NULL)
		dup_value = ft_strdup(value);
	node = NULL;
	if (dup_key != NULL && (value == NULL || dup_value != NULL))
		node = ms_env_new(dup_key, dup_value);
	if (node == NULL)
	{
		free(dup_key);
		free(dup_value);
		return (1);
	}
	ms_env_add(env, node);
	return (0);
}
