/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:37:21 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/08 04:48:55 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_H
# define CONF_H

# define MS_NAME	"Mishell"
# define DEBUG_MODE 1
// ------------------------------
// MISHEL CONFIGURATION

// ERRORS
// UPD == UNEXPECTED
# define ERR_NOT_FOUND		MS_NAME" : %s: command not found\n"
# define ERR_PERM_DENIED	MS_NAME" : %s: Permission denied\n"
# define ERR_SYNTAX_UPD_TOK	MS_NAME" : syntax error near unexpected token `%s'\n"
# define ERR_SYNTAX_UPD_EOF MS_NAME" : syntax error: unexpected `end of file'\n"
# define ERR_SYNTAX_UPD_NLN	MS_NAME" : syntax error: unexpected `newline'\n"
# define ERR_NOT_SUCH		MS_NAME" : %s: not such file or directory\n"
# define ERR_IS_DIR			MS_NAME" : %s: is a directory\n"
# define ERR_NO_FILE		MS_NAME" : %s: No such file or directory\n"
# define ERR_TOO_MANY_ARGS	MS_NAME" : Too many arguments\n"
# define ERR_EXECVE			MS_NAME" : execve failed\n"
# define ERR_MALLOC			MS_NAME" : malloc failed\n"
# define ERR_PIPE			MS_NAME" : pipe failed\n"
# define ERR_FD 			MS_NAME" : Bad file descriptor\n"	

// PARSER SYMBOLS

# define NO_WORD				"\'\"()\n|;&<> \t\\$*"
# define BLANK					" \t"
# define PARENTHESIS			"()"
# define S_BQUOTE				"`"
# define S_SQUOTE				"\'"
# define S_DQUOTE				"\""
# define S_P_OPEN				"("
# define S_P_CLOSE				")"
# define S_NEWLINE				"\n"
# define S_PIPE					"|"
# define S_SEMICOLON			";"
# define S_OR					"||"
# define S_AND_IF				"&&"
# define S_REDIR_OUT			">"
# define S_REDIR_IN				"<"
# define S_APPEND				">>"
# define S_HEREDOC				"<<"
# define S_SPACE				" "
# define S_TAB					"\t"
# define S_DOLLAR				"$"
# define S_BACKSLASH			"\\"
# define S_EOF					"\0"
# define S_WILDCARD				"*"
# define S_COMMENT				"#"

# define S_REDIR_INT_OUT		"<>"
# define S_SEP_CASE				";;"
# define S_AND					"&"
# define S_EXPR_OPEN			"(("
# define S_EXPR_CLOSE			"))"
# define S_SUBST_OPEN			"{{"
# define S_SUBST_CLOSE			"{{"
# define S_TEST_OPEN			"[ "
# define S_TEST_CLOSE			" ]"
# define S_HERESTRING			"<<<"

// SHELL builtins

// to do
# define B_ECHO					"echo" // with options -n
# define B_CD					"cd"
# define B_PWD					"pwd"
# define B_EXPORT				"export"
# define B_UNSET				"unset"
# define B_ENV					"env" // (no builtin)
# define B_EXIT					"exit"

// easy
# define B_TRUE					"true"
# define B_FALSE				"false"
# define B_HISTORY				"history"
# define B_ALIAS				"alias"
# define B_UNALIAS				"unalias"
# define B_KILL					"kill" // send signal to process
# define B_TIMES				"times" // show time usage
# define B_PRINTENV				"printenv" // (no builtin) alias -> env

# define B_LOCAL				"local" // declare var
# define B_READ					"read" //like echo
# define B_READARRAY			"readarray" // read lines from a file into an array
# define B_READONLY				"readonly" // mark variables as readonly
# define B_BREAK				"break"
# define B_CONTINUE				"continue"
# define B_RETURN				"return"
# define B_JOBS					"jobs" //create task
# define B_BG					"bg" // send task to background
# define B_FG					"fg" // send task to foreground
# define B_SET					"set" // set shell options
# define B_SHOPT				"shopt" // set shell options
# define B_GETOPT				"getopt" // parse positional parameters
# define B_SHIFT				"shift" // shift positional parameters 
# define B_TEST					"test"
# define B_TYPE					"type"
# define B_SOURCE				"source" // run file
# define B_EXEC					"exec" // replace shell with command
# define B_WAIT					"wait"
# define B_TRAP					"trap" // set signal handler
# define B_LOGOUT				"logout" // exit shell
# define B_DISOWN				"disown" // remove job from shell
# define B_BIND					"bind" // bind a key sequence to a readline function
# define B_BUILTIN				"builtin" // run a shell builtin (no search in PATH)
# define B_CALLER				"caller" // return context of current subroutine call
# define B_COMMAD				"command" // run command with optional args
# define B_DECLARE				"declare" // declare variables and give them attributes
# define B_ENABLE				"enable" // enable and disable builtin shell commands
# define B_HELP					"help" // display help for a builtin
# define B_COMPGEN				"compgen" // display possible completions
# define B_COMPLETE				"complete" // specify how arguments should be completed
# define B_COMPOPT				"compopt" // modify completion options for a command
# define B_HASH					"hash" // remember or forget commands
# define B_MAPFILE				"mapfile" // read lines from a file into an array
# define B_POPD					"popd" // remove directories from stack
# define B_PUSH					"pushd" // add directories to stack
# define B_SUSPEND				"suspend" // suspend shell execution
# define B_UMASK				"umask"
# define B_ULIMIT				"ulimit" // set or display resource limits
# define B_PRINTF				"printf" // format and print data
# define B_EVAL					"eval" // execute arguments as a shell command
# define B_CROCHET				"[" // WHAT??!!

// SHELL keywords

// # define K_NOT					"!"
# define K_COND_OPEN			"[["
# define K_COND_CLOSE			"]]"
# define k_GROUP_OPEN			"{"
# define K_GROUP_CLOSE			"}"
# define K_IF					"if"
# define K_THEN					"then"
# define K_TIME					"time"
# define K_ELSE					"else"
# define K_ELIF					"elif"
# define K_FI					"fi"
# define K_WHILE				"while"
# define K_DO					"do"
# define K_DONE					"done"
# define K_FOR					"for"
# define K_IN					"in"
# define K_SELECT				"select"
# define K_CASE					"case"
# define K_ESAC					"esac" // case end
# define K_FUNCTION				"function"
# define K_UNTIL				"until"

//COLORS

# define C_BLACK			"\033[0;30m"
# define C_RED				"\033[0;31m"
# define C_GREEN			"\033[0;32m"
# define C_YELLOW			"\033[0;33m"
# define C_BLUE				"\033[0;34m"
# define C_MAGENTA			"\033[0;35m"
# define C_CYAN				"\033[0;36m"
# define C_WHITE			"\033[0;37m"
# define C_RESET			"\033[0m"
# define C_BOLD				"\033[1m"

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

typedef enum e_metachar
{
	E_PIPE,
	E_SEMICOLON,
	E_AND
}	t_metachar;

enum e_rule {
	R_STOP = 0,
	R_NOT_INC = 1,
	R_INC = 2,
	R_OPER = 3,
	R_META = 4,
	R_CMP = 5
};

typedef struct {
	enum e_rule type;
	void *str;
	t_type value;
} t_rule;

typedef enum e_operator
{
	E_OR,
	E_AND_IF
}	t_operator;

#endif