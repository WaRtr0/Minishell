/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:41:01 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/05 15:59:35 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	ms_lexer_quote(t_shell *shell, t_prompt_s *status, t_parser_str *str)
{
	ms_add_join(shell, -1);
	if (str->type == E_SQUOTE || str->type == E_DQUOTE)
	{
		if (ms_reset_quote(status))
		{
			if (shell->command == NULL)
				shell->command = ft_strdup("");
			ms_append_quote(shell);
		}
	}
	else if (ms_reset_quote(status))
	{
		if (shell->command == NULL)
			shell->command = ft_select_str(&str->str[str->index], str->len);
		else
			ms_join_command(shell,
				ft_select_str(&str->str[str->index], str->len));
		ms_append_quote(shell);
	}
	else if (shell->command == NULL)
		shell->command = ft_select_str(&str->str[str->index], str->len);
	else
		ms_join_command(shell,
			ft_select_str(&str->str[str->index], str->len));
}
