/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 03:57:03 by gcros             #+#    #+#             */
/*   Updated: 2024/05/03 19:59:12 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	file_not_found(char *file);

int	exec_bin(t_exec *exec, t_shell *shell)
{
	char	*cmd;

	cmd = ms_get_exec_name(exec->content->data[0],
			ms_env_get(shell->env, "PATH"));
	if (cmd == NULL)
		return (file_not_found(exec->content->data[0]));
	return (0);
}

int	file_not_found(char *file)
{
	return (1);
}
