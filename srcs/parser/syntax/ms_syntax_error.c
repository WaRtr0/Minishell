/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:29:02 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 21:58:19 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "parser.h"

int	ms_syntax_error(t_error error, char *msg, t_shell *shell)
{
	if (!shell->prompt_listen)
		return (0);
	if (error == E_SYNTAX_UPD_TOK)
	{
		if (!msg)
		{
			shell->error = 1;
			shell->prompt_listen = 0;
			return (0);
		}
		printf(MS_NAME ERR_SYNTAX_TOK, msg);
	}
	else if (error == E_SYNTAX_UPD_EOF)
		printf(MS_NAME ERR_SYNTAX_UPD_EOF);
	else if (error == E_SYNTAX_UPD_NLN)
		printf(MS_NAME ERR_SYNTAX_UPD_NLN);
	if (!msg)
		free(msg);
	shell->prompt_listen = 0;
	return (0);
}
