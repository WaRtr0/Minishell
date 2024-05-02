/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:16:23 by gcros             #+#    #+#             */
/*   Updated: 2024/04/23 22:12:27 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

/**
 * @brief add a leaf or replace a value in the binary tree
 * 
 * @param head main env tree
 * @param e _leaf_ to add to main tree
 * @return error code (allways 0)
 */
int	ms_env_add(t_env **head, t_env *e)
{
	int	cmp;

	if (*head == NULL)
	{
		*head = e;
		return (0);
	}
	cmp = ft_strncmp((*head)->key, e->key, ft_strlen(e->key) + 1);
	if (cmp == 0)
	{
		free((*head)->value);
		(*head)->value = e->value;
		free(e->key);
		free(e);
		return (0);
	}
	else if (cmp < 0)
		return (ms_env_add(&(*head)->right, e));
	else
		return (ms_env_add(&(*head)->left, e));
	return (0);
}
