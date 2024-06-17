/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:25:23 by gcros             #+#    #+#             */
/*   Updated: 2024/06/11 19:35:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "str.h"
#include <stdint.h>
#include <fcntl.h>
#include "exec.h"
#include <errno.h>
#include "put.h"

void	print_exp(t_shell *shell, char *line, int fd);

void	print_hd(t_shell *shell, char *line, int fd, int expend)
{
	(void) shell;
	if (expend == 0)
		ft_putstr_fd(line, fd);
	else
	{
		print_exp(shell, line, fd);
	}
	ft_putendl_fd("", fd);
}

char	*get_var(t_shell *shell, char *word, size_t indent)
{
	char	*var;
	char	*env_var;

	if (indent == 1)
		return ("$");
	var = ft_substr(word, 0, indent);
	if (var == NULL)
		return ("");
	env_var = ms_env_get(shell->env, var + 1);
	free(var);
	if (env_var == NULL)
		return ("");
	return (env_var);
}

void	print_exp(t_shell *shell, char *line, int fd)
{
	size_t	indent;
	size_t	index;
	t_type	type;

	index = 0;
	while (line[index])
	{
		type = ms_get_type(&line[index]);
		indent = ms_get_indent(type, &line[index]);
		if (type == E_NAME)
			ft_putstr_fd(get_var(shell, &line[index], indent), fd);
		else
			write(fd, &line[index], indent);
		index += indent;
	}
}
