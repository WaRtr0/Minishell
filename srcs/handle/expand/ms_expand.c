/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:30:04 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/21 19:19:30 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "env.h"
#include "utils.h"

int	ms_expand(t_command *command, t_shell *shell, t_exec *exec_cmd, char **word)
{
	char	*env_str;
	char	**tmp_str;
	int		tmp;

	if (*word == NULL)
		*word = ft_strdup("");
	if (!ft_strlen(command->content.str))
		*word = ft_strjoin(*word, "$");
	else
	{
		env_str = ms_env_get(shell->env, command->content.str);
		if (command->type != CMD_EXPAND_QUOTE)
		{
			printf("A\n");
			if (env_str != NULL && env_str[0])
			{
				printf("B\n");
				tmp = ft_include(" \t", env_str[0]);
				tmp_str = ft_split_chars(env_str, " \t");
				if (*tmp_str != NULL && !tmp)
				{
					*word = ft_strjoin(*word, tmp_str[0]);
					if ((*(tmp_str + 1)) != NULL)
					{
						printf("D\n");
						ft_arr_append(exec_cmd->content, *word);
						*word = NULL;
					}
					tmp_str++;
				}
				printf("E\n");
				while (*tmp_str != NULL)
				{
					printf("E-A\n");
					if ((*(tmp_str + 1)) != NULL)
					{
						printf("E-B\n");
						ft_arr_append(exec_cmd->content, tmp_str);
					}
					else
						*word = *tmp_str;
					tmp_str++;
				}
			}
			printf("F\n");
		}
		else if (env_str != NULL)
			*word = ft_strjoin(*word, ft_strdup(env_str));
		else
			return (1);
		env_str = NULL;
	}
	printf("G\n");
	return (0);
}

// int	ms_expand(t_command *command, t_shell *shell, t_exec *exec_cmd, char *word)
// {
// 	if (word == NULL)
// 		word = ft_strdup("");

// 	//special
// 	if (!ft_strlen(command->content.str))
// 		word = ft_strjoin(word, "$");
// 	else
// 	{
// 		shell->command =  ms_env_get(shell->env,command->content.str);
// 		if (command->type != CMD_EXPAND_QUOTE)
// 		{
// 			if (shell->command != NULL && shell->command[0])
// 			{
// 				char	**temp_char;
// 				int		temp;
				
// 				temp = ft_include(" \t", shell->command[0]);
				
// 				temp_char = ft_split_chars(shell->command, " \t");
// 				if (*temp_char != NULL && !temp)
// 				{
// 					word = ft_strjoin(word, temp_char[0]);
// 					if ((*(temp_char + 1)) != NULL)
// 					{
// 						ft_arr_append(exec_cmd->content, word);
// 						word = NULL;
// 					}
// 					temp_char++;
// 				}
// 				while (*temp_char != NULL)
// 				{
// 					if ((*(temp_char + 1)) != NULL)
// 						ft_arr_append(exec_cmd->content, temp_char);
// 					else
// 						word = *temp_char;
// 					temp_char++;
// 				}
// 			}
// 		}
// 		else if (shell->command != NULL)
// 			word = ft_strjoin(word, ft_strdup(shell->command));	
// 		shell->command = NULL;
// 	}
// 	printf("G\n");
// 	return (0);
// }