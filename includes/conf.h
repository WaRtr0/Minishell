/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:37:21 by mmorot            #+#    #+#             */
/*   Updated: 2024/04/10 19:20:27 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_H
# define CONF_H

# define MS_NAME "mishell : "

// ------------------------------
// MISHEL CONFIGURATION

// ERRORS
// UPD == UNEXPECTED
# define ERR_NOT_FOUND		MS_NAME"%s: command not found\n"
# define ERR_PERM_DENIED	MS_NAME"%s: Permission denied\n"
# define ERR_SYNTAX_UPD_TOK	MS_NAME"syntax error near unexpected token `%s'\n"
# define ERR_SYNTAX_UPD_EOF MS_NAME"syntax error: unexpected end of file\n"
# define ERR_SYNTAX_UPD_NLN	MS_NAME"syntax error: unexpected newline\n"
# define ERR_NOT_SUCH		MS_NAME"%s: not such file or directory\n"
# define ERR_IS_DIR			MS_NAME"%s: is a directory\n"
# define ERR_NO_FILE		MS_NAME"%s: No such file or directory\n"
# define ERR_TOO_MANY_ARGS	MS_NAME"Too many arguments\n"
# define ERR_EXECVE			MS_NAME"execve failed\n"
# define ERR_MALLOC			MS_NAME"malloc failed\n"
# define ERR_PIPE			MS_NAME"pipe failed\n"
# define ERR_FD 			MS_NAME"Bad file descriptor\n"	


// PARSER SETTINGS

# define NO_WORD			"\'\"()\n|;&<> \t\\$*#"
# define BLANK				" \t"


# define S_SQUOTE				"\'"
# define S_DQUOTE				"\""
# define S_P_OPEN				"("
# define S_P_CLOSE			")"
# define S_NEWLINE			"\n"
# define S_PIPE				"|"
# define S_SEMICOLON			";"
# define S_AND				"&"
# define S_OR					"||"
# define S_AND_IF				"&&"
# define S_REDIR_OUT	"<"
# define S_REDIR_IN		">"
# define S_APPEND				">>"
# define S_HEREDOC			"<<"
# define S_HERESTRING			"<<<"
# define S_REDIR_INT_OUT		"<>"
# define S_SPACE				" "
# define S_TAB				"\t"
# define S_DOLLAR				"$"
# define S_BACKSLASH			"\\"
# define S_EOF				"\0"
# define S_WILDCARD			"*"
# define S_COMMENT			"#"

//COLORS

# define BLACK				"\033[0;30m"
# define RED				"\033[0;31m"
# define GREEN				"\033[0;32m"
# define YELLOW				"\033[0;33m"
# define BLUE				"\033[0;34m"
# define MAGENTA			"\033[0;35m"
# define CYAN				"\033[0;36m"
# define WHITE				"\033[0;37m"
# define RESET				"\033[0m"
# define BOLD				"\033[1m"

// ------------------------------
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
	E_WORD,
	E_NAME,
	E_OPERATOR,
	E_NEWLINE,
	E_HEREDOC,
	E_APPEND,
	E_REDIR_OUT,
	E_REDIR_IN,
	E_DQUOTE,
	E_SQUOTE,
	E_EMPTY,
	E_COMMENT,
	E_WILDCARD,
	E_EOF = -1
}	t_type;

typedef enum e_operator
{
	E_OR=21,
	E_AND_IF=22,
	E_AND=3,
	E_PIPE=4,
	E_SEMICOLON=5,
}	t_operator;



#endif