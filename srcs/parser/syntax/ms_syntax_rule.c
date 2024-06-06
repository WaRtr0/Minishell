/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_rule.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:06 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/06 16:21:24 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ms_syntax_rule(int type, char *str, t_shell *shell, t_prompt_s *status)
{
	if (status->no_print
		&& (type == E_WORD || type == E_NAME
			|| type == E_SQUOTE || type == E_DQUOTE)
		&& !status->chevron)
		ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
	if (type >= E_METACHAR && type <= E_OPERATOR && !ms_is_chevron(type)
		&& status->operator == 1 && !status->c_parenthesis)
		ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
	if (type >= E_PARENTHESIS && type <= E_OPERATOR && !ms_is_chevron(type)
		&& status->chevron == 1)
		ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
	if (ms_is_chevron(type) && status->chevron == 1)
		ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
	if ((type == E_METACHAR || type == E_OPERATOR) && status->print == 0
		&& !status->c_parenthesis)
		ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
	if (shell->prompt_listen)
		return (0);
	return (1);
}
