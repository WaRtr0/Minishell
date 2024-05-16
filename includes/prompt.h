/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:44:12 by gcros             #+#    #+#             */
/*   Updated: 2024/05/15 04:40:26 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

typedef enum e_command_type {
    CMD_PIPE,
    CMD_REDIR_IN,
    CMD_REDIR_OUT,
    CMD_APPEND,
    CMD_HEREDOC,
    CMD_SEMICOLON,
    CMD_AND_IF,
    CMD_AND,
    CMD_OR,
    CMD_QUOTE,
    CMD_PARENTHESIS,
    CMD_EXPAND,
    CMD_EXPAND_QUOTE,
    CMD_TEXT,
    CMD_JOIN,
    CMD_JOIN_NO_PRINT,
    CMD_EMPTY,
    CMD_WILDCARD
}  t_command_type;

typedef struct s_command {
    t_command_type  type;
    union   u_content   content;
}  t_command;

t_command   *ms_parse_command(char *line);
int ms_prompt(t_shell *shell);
#endif