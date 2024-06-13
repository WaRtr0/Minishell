/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:23:44 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/13 16:28:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	ms_add_str(t_shell *shell, t_command *command, t_parser_str *str)
{
	char	*tmp;

	if (command != NULL)
	{
		tmp = ft_select_str(&str->str[str->index], str->len);
		if (tmp == NULL)
		{
			shell->prompt_listen = 0;
			shell->error = 1;
			return ;
		}
		command->content.str = tmp;
	}
}
