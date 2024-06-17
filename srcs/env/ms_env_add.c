/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:16:23 by gcros             #+#    #+#             */
/*   Updated: 2024/06/13 23:45:23 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

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
}
