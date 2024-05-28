/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:30:04 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/28 16:20:11 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "env.h"
#include "utils.h"

static int	run_append(t_exec *exec_cmd, char **word, char **tmp_str)
{
	while (*tmp_str != NULL)
	{
		if ((*(tmp_str + 1)) != NULL)
			ft_arr_append(exec_cmd->content, *tmp_str);
		else
			*word = *tmp_str;
		tmp_str++;
	}
	return (0);
}

static int	expand_quote(t_exec *exec_cmd, char *env_str, char **word)
{
	char	**tmp_str;
	int		tmp;

	if (env_str != NULL && env_str[0])
	{
		tmp = ft_include(" \t\n", env_str[0]);
		tmp_str = ft_split_chars(env_str, " \t\n");
		if (*tmp_str != NULL && !tmp)
		{
			*word = ft_strjoin(*word, tmp_str[0]);
			if ((*(tmp_str + 1)) != NULL)
			{
				ft_arr_append(exec_cmd->content, *word);
				*word = NULL;
			}
			tmp_str++;
		}
		run_append(exec_cmd, word, tmp_str);
	}
	return (!(env_str != NULL && env_str[0]));
}

int	ms_expand(t_command *command, t_shell *shell, t_exec *exec_cmd, char **word)
{
	char	*env_str;

	if (*word == NULL)
		*word = ft_strdup("");
	if (!ft_strlen(command->content.str))
		*word = ft_strjoin(*word, "$");
	else
	{
		if (ft_strncmp(command->content.str, "?", 2) == 0)
			env_str = ft_itoa(ms_get_status());
		else
			env_str = ms_env_get(shell->env, command->content.str);
		if (command->type != CMD_EXPAND_QUOTE)
			return (expand_quote(exec_cmd, env_str, word));
		else if (env_str != NULL)
			*word = ft_strjoin(*word, ft_strdup(env_str));
		else
			return (1);
		env_str = NULL;
	}
	return (0);
}
