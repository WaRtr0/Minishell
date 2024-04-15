/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:44:12 by gcros             #+#    #+#             */
/*   Updated: 2024/04/15 19:20:31 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

typedef struct s_prompt_status {
    int     started;
    int     quote;
    int     squote;
    int     dquote;
    int     print;
    int     chevron;
    int     heredoc;
    int     operator;
    int     parenthesis;
    int     c_parenthesis;
    int     last_parenthesis;
    int     newline;
}   t_prompt_status;

int ms_prompt(t_shell *shell);
#endif