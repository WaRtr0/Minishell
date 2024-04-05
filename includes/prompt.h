/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:44:12 by gcros             #+#    #+#             */
/*   Updated: 2024/04/05 06:40:05 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

typedef struct s_prompt_status {
    int     started;
    int     white;
    int     quote;
    int     dquote;
    int     operator;
    int     newline;
    int     append;
    int     print;
    int     chevron_left;
    int     chevron_right;
    int     heredoc;
    int     metachar;
    int     parenthesis;
}   t_prompt_status;

int ms_prompt(t_shell *shell);
#endif