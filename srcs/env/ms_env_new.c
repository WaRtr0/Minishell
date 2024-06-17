/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:20:52 by gcros             #+#    #+#             */
/*   Updated: 2024/06/13 23:46:13 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

t_env	*ms_env_new(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env != NULL)
		ms_env_init(key, value, env);
	return (env);
}
