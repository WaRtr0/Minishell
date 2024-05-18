/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:19:27 by wartro            #+#    #+#             */
/*   Updated: 2024/05/18 06:28:14 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>

// libft
# include "char.h"
# include "str.h"
# include "arr.h"
# include "env.h"

typedef enum e_error
{
	E_NOT_FOUND,
	E_PERM_DENIED,
	E_SYNTAX_UPD_TOK,
	E_SYNTAX_UPD_EOF,
	E_SYNTAX_UPD_NLN,
	E_NOT_SUCH,
	E_IS_DIR,
	E_NO_FILE,
	E_TOO_MANY_ARGS,
	E_EXECVE,
	E_MALLOC,
	E_EXEC
}	t_error;
typedef enum e_type
{
	E_EOF = -1,
	E_DQUOTE,
	E_SQUOTE,
	E_PARENTHESIS,
	E_NEWLINE,
	E_METACHAR,
	E_REDIR_OUT,
	E_REDIR_IN,
	E_HEREDOC,
	E_APPEND,
	E_OPERATOR,
	E_WILDCARD,
	E_WORD,
	E_NAME,
	E_EMPTY
}	t_type;

typedef struct s_prompt_s
{
	int	started;
	int	squote;
	int	dquote;
	int	no_print;
	int	print;
	int	chevron;
	int	heredoc;
	int	no_empty;
	int	operator;
	int	parenthesis;
	int	c_parenthesis;
	int	last_parenthesis;
	int	newline;
}	t_prompt_s;


typedef enum e_metachar
{
	E_PIPE,
	E_SEMICOLON,
	E_AND
}	t_metachar;

enum	e_rule
{
	R_STOP = 0,
	R_NOT_INC = 1,
	R_INC = 2,
	R_OPER = 3,
	R_META = 4,
	R_CMP = 5
};

typedef struct s_rule
{
	enum e_rule	type;
	void		*str;
	t_type		value;
}	t_rule;

typedef enum e_operator
{
	E_OR,
	E_AND_IF
}	t_operator;

// utils
int		ms_is_chevron(t_type type);
int		ms_is_semicolon(t_type type, char *line);
int		ms_get_indent(t_type value, char *str);
t_type	ms_get_type(char *str);

int		ms_inc_word(const char *str);
int		ms_inc_name(const char *str);
int		ms_inc_blank(const char *str);

int		ms_get_operator(char *str);
int		ms_get_metachar(char *str);

int		ms_reset_quote(t_prompt_s *status);

// parser - heredoc
int		ms_heredoc(t_shell *shell, char *limiter);

// parser - syntax
int		ms_syntax_error(t_error error, char *msg, t_shell *shell);
int		ms_syntax_rule(int type, char *str, t_shell *shell, t_prompt_s *status);

int		ms_parser(char *line, t_prompt_s *status, t_shell *shell);

#endif