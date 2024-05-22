/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:38:50 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/23 00:37:08 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "parser.h"

typedef enum e_command_type
{
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
}	t_command_type;

typedef struct s_command
{
	t_command_type		type;
	union u_content		content;
}	t_command;

t_command		*ms_new_command(t_shell *shell);
void			ms_commit_command(t_shell *shell, t_command *command);
void			ms_add_type(t_command *command, int type);
void			ms_add_str(t_shell *shell,
					t_command *command, t_parser_str *str);
void			ms_add_fd(t_command *command, int fd);
void			*ms_clear_command(t_command *command);
int				ms_get_command_type(t_command *command);

void			ms_lexer(t_shell *shell, t_prompt_s *status,
					int type, t_parser_str *str);
//utils
t_command		*ms_get_children(t_shell *shell, size_t children);
t_command		*ms_get_parent(t_shell *shell, size_t parent);
t_command		*ms_get_cursor(t_shell *shell);
t_command_type	ms_get_cmd(int type, char *str);
int				ms_get_cursor_type(t_shell *shell);

int				ms_is_pipeline(t_shell *shell);
int				ms_is_join(t_shell *shell);
int				ms_is_parenthesis(t_shell *shell);

void			ms_add_pipeline(t_shell *shell);
void			ms_add_join(t_shell *shell, int type );

void			ms_exit_pipeline(t_shell *shell);
void			ms_exit_join(t_shell *shell);

void			ms_append_quote(t_shell *shell);

//actions
void			ms_lexer_empty(t_shell *shell);
void			ms_lexer_wildcard(t_shell *shell,
					t_parser_str *str);
void			ms_lexer_quote(t_shell *shell,
					t_prompt_s *status, t_parser_str *str);
void			ms_lexer_redir(t_shell *shell,
					t_prompt_s *status, t_parser_str *str);
void			ms_lexer_name(t_shell *shell,
					t_prompt_s *status, t_parser_str *str);
void			ms_lexer_heredoc(t_shell *shell,
					t_prompt_s *status);
void			ms_lexer_operator(t_shell *shell,
					t_prompt_s *status, t_parser_str *str);
void			ms_lexer_parenthesis(t_shell *shell,
					t_prompt_s *status, t_parser_str *str);
#endif