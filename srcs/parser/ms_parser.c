/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:18:57 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 00:30:39 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "conf.h"
#include "str.h"
#include "utils.h"

static void	run_parsing(char *line, t_prompt_s *status,
	t_shell *shell)
{
	t_parser_str	str;

	str.index = 0;
	str.str = line;
	while (line[str.index])
	{
		str.type = ms_get_type(&line[str.index]);
		if (str.type == E_EOF)
			break ;
		str.len = ms_get_indent(str.type, &line[str.index]);
		if (str.type == E_METACHAR
			&& ms_get_metachar(&line[str.index]) == E_AND)
			str.type = E_WORD;
		if (!status->squote && !status->dquote)
		{
			ms_syntax_rule(str.type,
				ft_select_str(&line[str.index], str.len), shell, status);
			ms_update_status_text(status, str.type);
			ms_update_status_heredoc(status, str.type);
			if (status->heredoc && status->print)
				ms_heredoc(shell, ft_select_str(&line[str.index], str.len));
			ms_update_status_operator(status, str.type, &str);
			if (str.type == E_PARENTHESIS)
				ms_lexer_parenthesis(shell, status, &str);
		}
		ms_update_status_quote(status, str.type);
		if (shell->prompt_listen == 0 || shell->error > 0)
			break ;
		ms_lexer(shell, status, str.type, &str);
		str.index += str.len;
		str.len = 0;
	}
}

static void	recursive_parser(t_shell *shell, t_prompt_s *status)
{
	char		*newline;

	while (status->heredoc || status->squote
		|| status->dquote || status->parenthesis || status->newline)
	{
		newline = readline("> ");
		if (!newline)
			break ;
		ms_parser(newline, status, shell);
		if (shell->prompt_listen == 0)
			break ;
		if (newline)
			free(newline);
	}
}

static void	join_parsers(t_shell *shell, t_prompt_s *status, char *line)
{
	char	*newline;

	if (status->dquote || status->squote)
	{
		if (shell->command == NULL)
			shell->command = ft_strdup("\n");
		else
			shell->command = ft_strjoin(shell->command, ft_strdup("\n"));
	}
	if (shell->prompt_listen)
	{
		newline = shell->prompt;
		if (status->parenthesis)
		{
			if (status->print
				|| status->parenthesis != status->last_parenthesis)
				shell->prompt = ft_strjoin_seperator(shell->prompt, line, "; ");
			else
				shell->prompt = ft_strjoin_seperator(shell->prompt, line, " ");
		}
		else if (status->newline)
		{
			status->newline = 0;
			shell->prompt = ft_strjoin_seperator(shell->prompt, line, " ");
		}
		else
			shell->prompt = ft_strjoin_seperator(shell->prompt, line, "\n");
		replace_history_entry(shell->line, shell->prompt, NULL);
		free(newline);
	}
}

int	ms_parser(char *line, t_prompt_s *status, t_shell *shell)
{
	if (ft_strlen(line) <= 0)
		return (0);
	join_parsers(shell, status, line);
	shell->prompt_listen = 1;
	status->no_print = 0;
	run_parsing(line, status, shell);
	if (status->chevron)
		ms_syntax_error(E_SYNTAX_UPD_NLN, NULL, shell);
	if (shell->prompt_listen == 0 || shell->error > 0)
		return (0);
	recursive_parser(shell, status);
	return (1);
}
