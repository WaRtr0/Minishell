/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:37:21 by mmorot            #+#    #+#             */
/*   Updated: 2024/04/05 01:46:17 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_H
# define CONF_H

# define NAME "mishell : "

// ERRORS
// UPD == UNEXPECTED
# define ERR_NOT_FOUND		NAME"%s: command not found\n"
# define ERR_PERM_DENIED	NAME"%s: Permission denied\n"
# define ERR_SYNTAX_UPD_TOK	NAME"syntax error near unexpected token `%s'\n"
# define ERR_SYNTAX_UPD_EOF NAME"syntax error: unexpected end of file\n"
# define ERR_SYNTAX_UPD_NLN	NAME"syntax error: unexpected newline\n"
# define ERR_NOT_SUCH		NAME"%s: not such file or directory\n"
# define ERR_IS_DIR			NAME"%s: is a directory\n"
# define ERR_NO_FILE		NAME"%s: No such file or directory\n"
# define ERR_TOO_MANY_ARGS	NAME"Too many arguments\n"
# define ERR_EXECVE			NAME"execve failed\n"
# define ERR_MALLOC			NAME"malloc failed\n"
# define ERR_PIPE			NAME"pipe failed\n"

typedef enum e_error
{
	NOT_FOUND,
	PERM_DENIED,
	SYNTAX_UPD_TOK,
	SYNTAX_UPD_EOF,
	SYNTAX_UPD_NLN,
	NOT_SUCH,
	IS_DIR,
	NO_FILE,
	TOO_MANY_ARGS,
	EXECVE,
	MALLOC,
	PIPE
}	t_error;

#endif