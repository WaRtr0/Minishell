/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:10:20 by gcros             #+#    #+#             */
/*   Updated: 2024/05/21 15:46:38 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "put.h"

char	*ms_expends(t_shell *shell, char *str)
{
	char	*s;

	ft_putendl_fd(str, 2);
	s = NULL;
	if (ft_strncmp(str, "?", 2) == 0)
		return (ft_itoa(shell->status));
	s = ms_env_get(shell->env, str);
	if (s != NULL)
		s = ft_strdup(s);
	return (s);
}
