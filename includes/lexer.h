#ifndef LEXER_H
#  define LEXER_H

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

t_command		*ms_get_children(t_shell *shell, size_t children);
t_command		*ms_get_parent(t_shell *shell, size_t parent);
t_command		*ms_get_cursor(t_shell *shell);
t_command_type	ms_get_cmd(int type, char *str);

int				ms_is_pipeline(t_shell *shell);
int				ms_is_join(t_shell *shell);

void			ms_add_pipeline(t_shell *shell);
void			ms_add_join(t_shell *shell, int type );

void			ms_exit_pipeline(t_shell *shell);
void			ms_exit_join(t_shell *shell);

void			ms_append_quote(t_shell *shell);
#endif