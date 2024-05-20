/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:43:55 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/20 15:43:59 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "parser.h"
#include "utils.h"

t_type	ms_get_type(char *str)
{
	const t_rule	rule[] = {{R_NOT_INC, NO_WORD, E_WORD},
	{R_INC, BLANK, E_EMPTY}, {R_INC, PARENTHESIS, E_PARENTHESIS},
	{R_OPER, NULL, E_OPERATOR}, {R_META, NULL, E_METACHAR},
	{R_CMP, S_DQUOTE, E_DQUOTE}, {R_CMP, S_SQUOTE, E_SQUOTE},
	{R_CMP, S_HEREDOC, E_HEREDOC}, {R_CMP, S_APPEND, E_APPEND},
	{R_CMP, S_REDIR_OUT, E_REDIR_OUT}, {R_CMP, S_REDIR_IN, E_REDIR_IN},
	{R_CMP, S_WILDCARD, E_WILDCARD}, {R_CMP, S_NEWLINE, E_NEWLINE},
	{R_CMP, S_DOLLAR, E_NAME}, {R_STOP, NULL, E_EOF}};
	size_t			i;

	i = 0;
	while (!(rule[i].type == R_STOP
			|| (rule[i].type == R_NOT_INC && !ft_include(rule[i].str, str[0]))
			|| (rule[i].type == R_INC && ft_include(rule[i].str, str[0]))
			|| (rule[i].type == R_OPER && ms_get_operator(str) != -1)
			|| (rule[i].type == R_META && ms_get_metachar(str) != -1)
			|| (rule[i].type == R_CMP && !ft_strncmp(str, rule[i].str,
					ft_strlen(rule[i].str)))))
	{
		printf("%ld\n", i);
		i++;
	}
	return (rule[i].value);
}
