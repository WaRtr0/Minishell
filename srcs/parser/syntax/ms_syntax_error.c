/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:29:02 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/24 17:27:38 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.h"
#include "parser.h"
#include "put.h"

int	ms_syntax_error(t_error error, char *msg, t_shell *shell)
{
	char	*str;

	if (shell->prompt_listen == 0)
		return (0);
	shell->prompt_listen = 0;
	ms_set_status(2 << 8);
	str = NULL;
	if (error == E_SYNTAX_UPD_TOK)
	{
		if (!msg)
			shell->error = 1;
		if (!msg)
			return (0);
		str = ft_strsjoin((char *[])
			{"Mishell: syntax error near unexpected token `", msg, "`", NULL});
	}
	else if (error == E_SYNTAX_UPD_EOF)
		str = ft_strdup("Mishell: syntax error: unexpected `end of file'");
	else if (error == E_SYNTAX_UPD_NLN)
		str = ft_strdup("Mishell: syntax error: unexpected `newline'");
	if (str)
		ft_putendl_fd(str, 2);
	free(msg);
	free(str);
	return (0);
}
