/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:44:37 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/11 19:09:24 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "expand.h"
#include "utils.h"

static	void process_tokens(char **tokens, t_array *new_array)
{
	char *temp;

    if (*tokens != NULL && !ft_include(" \t\n", (*tokens)[0]))
	{
        if (ms_is_last_type_text_or_expand(new_array))
		{
            temp = ms_get_last_command(new_array)->content.str;
            if (ms_get_last_type(new_array) == CMD_EXPAND && *ms_get_last_char(temp) == '$')
				*ms_get_last_char(temp) = '\0';
			if (ft_include(*tokens, '*'))
				ms_get_last_command(new_array)->type = CMD_WILDCARD;
            ms_get_last_command(new_array)->content.str = ft_strjoin(temp, *tokens);
            free(temp);
        }
		else
            ms_append_new_command_str(new_array, CMD_EXPAND, *tokens);
        tokens++;
    }
    while (*tokens != NULL)
	{
        ms_handle_cmd_empty(new_array);
        ms_append_new_command_str(new_array, CMD_EXPAND, *tokens);
        tokens++;
    }
}

static	void handle_expanded_str(char *str, t_array *new_array, t_shell *shell)
{
    char    *env_str;
	char    **tokens;

	env_str = ms_get_exp(str, shell->env);
    if (env_str != NULL && env_str[0])
	{
        if (ft_include(" \t\n",env_str[0]))
            ms_handle_cmd_empty(new_array);
        tokens = ft_split_chars(env_str, " \t\n");
        process_tokens(tokens, new_array);
        if (ft_include(" \t\n",env_str[ft_strlen(env_str) - 1]))
            ms_handle_cmd_empty(new_array);
        ft_strsfree(tokens);
    }
    free(env_str);
}

void	ms_handle_cmd_expand(t_command *command, t_array *new_array,
		t_shell *shell) {
	if (command->content.str[0] == '\0')
	{
		if (ms_is_last_type_text_or_expand(new_array))
			ms_update_last_command_type(new_array, CMD_EXPAND, "$");
		else
			ms_append_new_command_str(new_array, CMD_EXPAND, "$");
	}
	else
		handle_expanded_str(command->content.str, new_array, shell);
}
