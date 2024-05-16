/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_collapse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:18:21 by gcros             #+#    #+#             */
/*   Updated: 2024/04/16 04:50:36 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

/**
 * @brief destroy the actual env tree and the leafs
 * 
 * @param head the top of the tree
 */
void	ms_env_collapse(t_env **head)
{
	if (*head == NULL)
		return ;
	free((*head)->key);
	free((*head)->value);
	ms_env_collapse(&(*head)->left);
	ms_env_collapse(&(*head)->right);
	(*head)->key = NULL;
	(*head)->value = NULL;
	free(*head);
	*head = NULL;
}
