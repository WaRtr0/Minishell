/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:16:41 by gcros             #+#    #+#             */
/*   Updated: 2024/04/06 00:39:18 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>
#include "str.h"

static void	ms_env_rm_node(t_env **head);

/**
 * @brief remove a node from a key
 * 
 * @param head the head of the env tree
 * @param key the key to remove
 */
void	ms_env_remove(t_env	**head, char *key)
{
	int	cmp;

	if (*head == NULL)
		return ;
	cmp = ft_strncmp((*head)->key, key, ft_strlen(key) + 1);
	if (cmp == 0)
		ms_env_rm_node(head);
	else if (cmp < 0)
		return (ms_env_remove(&(*head)->right, key));
	else
		return (ms_env_remove(&(*head)->left, key));
	return ;
}

/**
 * @brief remove the actual node from the tree
 * 
 * @param head the node to remove
 */
static void	ms_env_rm_node(t_env **head)
{
	t_env	*tmp;

	free((*head)->key);
	free((*head)->value);
	tmp = *head;
	(*head)->key = NULL;
	(*head)->value = NULL;
	if ((*head)->left == NULL && (*head)->right == NULL)
		*head = NULL;
	else if ((*head)->left == NULL)
		*head = tmp->right;
	else if ((*head)->right == NULL)
		*head = tmp->left;
	else
	{
		*head = tmp->left;
		ms_env_add(head, tmp->right);
	}
	free(tmp);
}
