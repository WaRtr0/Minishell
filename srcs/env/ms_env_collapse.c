/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_collapse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:18:21 by gcros             #+#    #+#             */
/*   Updated: 2024/06/13 23:45:27 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

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
