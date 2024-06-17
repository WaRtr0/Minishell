/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:18:42 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/10 05:24:01 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_exp(char *str, t_env *env)
{
	char	*nstr;

	if (ft_strncmp(str, "?", 2) == 0)
		nstr = ft_itoa(ms_get_status());
	else
	{
		nstr = ms_env_get(env, str);
		if (nstr == NULL)
			return (NULL);
		nstr = ft_strdup(nstr);
	}
	return (nstr);
}
