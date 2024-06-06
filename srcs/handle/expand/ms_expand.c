/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:30:04 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/06 21:10:57 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "env.h"
#include "utils.h"

static int	run_append(t_exec *exec_cmd, char **word, char **tmp_str)
{
	char	*tmp_tmp_str;

	while (*tmp_str != NULL)
	{
		tmp_tmp_str = ft_strdup(*tmp_str);
		if ((*(tmp_str + 1)) != NULL)
			ft_arr_append(exec_cmd->content, tmp_tmp_str);
		else
			*word = tmp_tmp_str;
		tmp_str++;
	}
	return (0);
}

char	*fj(char *s1, char *s2)
{
	char	*t;

	t = s1;
	s1 = ft_strjoin(s1, s2);
	free(t);
	return (s1);
}

static int	expand_quote(t_exec *exec_cmd, char *env_str, char **word)
{
	char	**tmp_str;
	char	**tmp_tmp_str;
	int		tmp;

	if (env_str != NULL && env_str[0])
	{
		tmp_str = ft_split_chars(env_str, " \t\n");
		tmp_tmp_str = tmp_str;
		if (*tmp_str != NULL && !ft_include(" \t\n", env_str[0]))
		{
			*word = fj(*word, tmp_str[0]);
			if ((*(tmp_str + 1)) != NULL)
			{
				ft_arr_append(exec_cmd->content, *word);
				*word = NULL;
			}
			tmp_str++;
		}
		run_append(exec_cmd, word, tmp_str);
		if (tmp_tmp_str)
			ft_strsfree(tmp_tmp_str);
	}
	tmp = !(env_str != NULL && env_str[0]);
	free(env_str);
	return (tmp);
}

char	*get_exp(char *str, t_env *env)
{
	char	*nstr;

	if (ft_strncmp(str, "?", 2) == 0)
	{
		nstr = ft_itoa(ms_get_status());
	}
	else
	{
		nstr = ms_env_get(env, str);
		if (nstr == NULL)
			return (NULL);
		nstr = ft_strdup(nstr);
	}
	return (nstr);
}

int	ms_expand(t_command *command, t_shell *shell, t_exec *exec_cmd, char **word)
{
	char	*env_str;

	if (*word == NULL)
		*word = ft_strdup("");
	if (ft_strlen(command->content.str) == 0)
		*word = fj(*word, "$");
	else
	{
		env_str = get_exp(command->content.str, shell->env);
		if (command->type != CMD_EXPAND_QUOTE)
			return (expand_quote(exec_cmd, env_str, word));
		else if (env_str != NULL)
			*word = fj(*word, env_str);
		else
		{
			free(env_str);
			free(command->content.str);
			ms_add_type(command, CMD_EMPTY);
			return (1);
		}
		free(env_str);
	}
	return (0);
}
