/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_join_parsers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:54:25 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/05 18:16:10 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "prompt.h"
#include "utils.h"

static void	join_quote(t_shell *shell, t_prompt_s *status)
{
	if (status->dquote || status->squote)
	{
		if (shell->command == NULL)
			shell->command = ft_strdup("\n");
		else
			ms_join_command(shell, ft_strdup("\n"));
	}
}

static void	join_parenthesis(t_shell *shell, t_prompt_s *status, char *line)
{
	t_parser_str	str;
	if (status->print
		|| status->parenthesis != status->last_parenthesis)
	{
		ms_join_prompt(shell, line, "; ");
		str.type = E_METACHAR;
		str.str = ";";
		str.len = 1;
		str.index = 0;
		ms_lexer_operator(shell, status, &str);
	}
	else
		ms_join_prompt(shell, line, " ");
}

static void	join_operator(t_shell *shell, t_prompt_s *status, char *line)
{
	status->newline = 0;
	ms_join_prompt(shell, line, " ");
}

void	ms_join_parsers(t_shell *shell, t_prompt_s *status, char *line)
{
	char	*newline;

	join_quote(shell, status);
	if (shell->prompt_listen)
	{
		newline = shell->prompt;
		if (status->parenthesis)
		{
			join_parenthesis(shell, status, line);
		}
		else if (status->newline)
		{
			join_operator(shell, status, line);
		}
		else
			ms_join_prompt(shell, line, "\n");
		// replace_history_entry(shell->line, shell->prompt, NULL);
		free(newline);
	}
}
