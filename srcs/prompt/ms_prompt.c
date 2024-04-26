/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by mmorot            #+#    #+#             */
/*   Updated: 2024/04/27 00:16:02 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ms_prompt.c
 * @brief Fichier qui contient la fonction qui va lancer le prompt
 *
 */
#include "arr.h"
#include "char.h"
#include "conf.h"
#include "minishell.h"
#include "prompt.h"
#include "str.h"
// #include "num.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int	ms_syntax_error(t_error error, char *msg, t_shell *shell)
{
	if (!shell->prompt_listen)
		return (0);
	if (error == E_SYNTAX_UPD_TOK)
	{
		printf(ERR_SYNTAX_UPD_TOK, msg);
		free(msg);
	}
	else if (error == E_SYNTAX_UPD_EOF)
		printf(ERR_SYNTAX_UPD_EOF);
	else if (error == E_SYNTAX_UPD_NLN)
		printf(ERR_SYNTAX_UPD_NLN);
	shell->prompt_listen = 0;
	return (0);
}

//// A RAJOUTER
int	ft_include(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_countwords_char(char const *str, char *sep)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_include(sep, *str))
			str++;
		if (*str && !ft_include(sep, *str))
			count++;
		while (*str && !ft_include(sep, *str))
			str ++;
	}
	return (count);
}

static char	*ft_getnextword_char(char const *str, char *sep)
{
	char	*buf;
	size_t	i;

	while (*str && ft_include(sep, *str))
		str++;
	i = 0;
	while (str[i] && !ft_include(sep, str[i]))
		i++;
	buf = (char *) malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && !ft_include(sep, str[i]) && buf)
	{
		buf[i] = str[i];
		i++;
	}
	if (buf)
		buf[i] = '\0';
	return (buf);
}

static void	ft_freebuf(char ***buf)
{
	ft_strsfree(buf[0]);
	buf[0] = NULL;
}

char	**ft_split_chars(char const *s, char *c)
{
	size_t		count;
	char		**buf;
	size_t		i;
	char const	*str;

	str = s;
	count = ft_countwords_char(str, c);
	buf = (char **) malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count && buf)
	{
		buf[i] = ft_getnextword_char(str, c);
		if (!buf[i])
			ft_freebuf(&buf);
		while (*str && ft_include(c,*str))
			str++;
		while (*str && !ft_include(c,*str))
			str++;
		i++;
	}
	if (buf)
		buf[count] = NULL;
	return (buf);
}

////end

char	*select_str(char *str, size_t n)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	while (i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	get_operator(char *str)
{
	if (!ft_strncmp(str, S_OR, ft_strlen(S_OR)))
		return (E_OR);
	if (!ft_strncmp(str, S_AND_IF, ft_strlen(S_AND_IF)))
		return (E_AND_IF);
	return (-1);
}


int	get_metachar(char *str)
{
	if (!ft_strncmp(str, S_AND, ft_strlen(S_AND)))
		return (E_AND);
	if (!ft_strncmp(str, S_PIPE, ft_strlen(S_PIPE)))
		return (E_PIPE);
	if (!ft_strncmp(str, S_SEMICOLON, ft_strlen(S_SEMICOLON)))
		return (E_SEMICOLON);
	return (-1);
}

int	pass_blank(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_include(BLANK, str[i]))
		i++;
	return (i);
}

int	pass_word(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_include(NO_WORD, str[i]))
		i++;
	return (i);
}

int	pass_name(const char *str)
{
	size_t	i;

	i = 1;
	while (str[i] && (ft_isdigit(str[i]) || ft_isalpha(str[i]) || ft_include("_", str[i])))
		i++;
	return (i);
}



t_type	get_type(char *str)
{
	if (!ft_include(NO_WORD, str[0]))
		return (E_WORD);
	if (ft_include(BLANK, str[0]))
		return (E_EMPTY);
	if (ft_include(PARENTHESIS, str[0]))
		return (E_PARENTHESIS);
	if (get_operator(str) != -1)
		return (E_OPERATOR);
	if (get_metachar(str) != -1)
		return (E_METACHAR);
	if (!ft_strncmp(str, S_DQUOTE, ft_strlen(S_DQUOTE)))
		return (E_DQUOTE);
	if (!ft_strncmp(str, S_SQUOTE, ft_strlen(S_SQUOTE)))
		return (E_SQUOTE);
	if (!ft_strncmp(str, S_HEREDOC, ft_strlen(S_HEREDOC)))
		return (E_HEREDOC);
	if (!ft_strncmp(str, S_APPEND, ft_strlen(S_APPEND)))
		return (E_APPEND);
	if (!ft_strncmp(str, S_REDIR_OUT, ft_strlen(S_REDIR_OUT)))
		return (E_REDIR_OUT);
	if (!ft_strncmp(str, S_REDIR_IN, ft_strlen(S_REDIR_IN)))
		return (E_REDIR_IN);
	if (!ft_strncmp(str, S_WILDCARD, ft_strlen(S_WILDCARD)))
		return (E_WILDCARD);
	if (!ft_strncmp(str, S_NEWLINE, ft_strlen(S_NEWLINE)))
		return (E_NEWLINE);
	if (!ft_strncmp(str, S_DOLLAR, ft_strlen(S_DOLLAR)))
		return (E_NAME);
	return (E_EOF);
}

int	next_indent(t_type value, char *str)
{
	if (value >= E_HEREDOC && value <= E_OPERATOR)
		return (2);
	if ((value >= E_DQUOTE && value <= E_COMMENT) || value == E_WILDCARD)
		return (1);
	if (value == E_WORD)
		return (pass_word(str));
	if (value == E_NAME)
		return (pass_name(str));
	if (value == E_EMPTY)
		return (pass_blank(str));
	return (-1);
}
	
int is_chevron(t_type type)
{
    if (type == E_REDIR_IN || type == E_REDIR_OUT || type == E_APPEND || type == E_HEREDOC)
        return (1);
    return (0);
}

int	get_line(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			j++;
		i++;
	}
	return (j);
}

int	add_fd(t_shell *shell)
{
	(void)shell;
	int		fd[2];
	// 0 = read
	// 1 = write

	if (pipe(fd) == -1)
	{
		perror(ERR_PIPE);
		return (1);
	}
	if (!ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fd[0]))
	{
		perror(ERR_MALLOC);
		return (1);
	}
	if (!ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fd[1]))
	{
		perror(ERR_MALLOC);
		return (1);
	}
	shell->heredoc_size += 2;
	return (0);
}

int is_semicolon(t_type type, char *line)
{
	if (type == E_METACHAR && ft_strncmp(line, ";", 1) == 0)
		return (1);
	return (0);
}

char *ft_strjoin_seperator(char *s1, char *s2, char *sep)
{
    char *new;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep) + 1));
    if (!new)
        return (NULL);
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    while (sep[j])
    {
        new[i] = sep[j];
        i++;
        j++;
    }
    j = 0;
    while (s2[j])
    {
        new[i] = s2[j];
        i++;
        j++;
    }
    new[i] = '\0';
    return (new);
}

t_command_type	get_CMD(int type, char *str)
{
	if (type == E_OPERATOR)
	{
		if (get_operator(str) == E_OR)
			return (CMD_OR);
		if (get_operator(str) == E_AND_IF)
			return (CMD_AND_IF);
	}
	if (type == E_METACHAR)
	{
		if (get_metachar(str) == E_AND)
			return (CMD_AND);
		if (get_metachar(str) == E_PIPE)
			return (CMD_PIPE);
		if (get_metachar(str) == E_SEMICOLON)
			return (CMD_SEMICOLON);
	}
	if (type == E_REDIR_IN)
		return (CMD_REDIR_IN);
	if (type == E_REDIR_OUT)
		return (CMD_REDIR_OUT);
	if (type == E_APPEND)
		return (CMD_APPEND);
	return (CMD_TEXT);
}

t_command   *get_children(t_shell *shell, size_t children)
{
    size_t size_array;
    size_t size_cursor;

    size_array = shell->cursor_array->size;
    if (size_array == 0 ||  1 > size_array)
        return (NULL);
    size_cursor = ((t_array *)shell->cursor_array->data[size_array - 1])->size;
    if (size_cursor == 0 || children <= 0 || children > size_cursor)
        return (NULL);
    return ((t_command *)(((t_array *)shell->cursor_array->data[size_array - 1])->data[size_cursor - children]));
}

t_command   *get_parent(t_shell *shell, size_t parent)
{
    size_t size_array;
    size_t size_cursor;

    size_array = shell->cursor_array->size;
    if (size_array == 0 || parent == 0 || parent > size_array)
        return (NULL);
    size_cursor = ((t_array *)shell->cursor_array->data[size_array - parent])->size;
    if (size_cursor == 0)
        return (NULL);
    return ((t_command *)(((t_array *)shell->cursor_array->data[size_array - parent])->data[size_cursor - 1]));
}

t_command	*actual_cursor(t_shell *shell)
{
	if (((t_array *)shell->cursor)->size > 0)
	{
		return (
			(t_command *)(
				(t_array *)shell->cursor
				)->data[
					(
						(t_array *)shell->cursor
					)->size - 1
				]
		);
	}
	return (NULL);
}

int	on_pipe(t_shell *shell)
{
	if (shell->cursor_array->size > 0 && get_parent(shell, 1) != NULL && get_parent(shell, 1)->type == CMD_PIPE)
		return (1);
	return (0);
}

void add_pipe(t_shell *shell)
{
	t_command *append_command;

	if (!on_pipe(shell))
	{
		append_command = malloc(sizeof(t_command));
		append_command->type = CMD_PIPE;
		append_command->content.array = ft_arr_new(10);
		ft_arr_append(shell->cursor, append_command);
		ft_arr_append(shell->cursor_array, shell->cursor);
		shell->cursor = append_command->content.array;
	}
}

void exit_pipe(t_shell *shell)
{
	if (on_pipe(shell))
		shell->cursor = ft_arr_pop(shell->cursor_array);
}
int	on_join(t_shell *shell)
{
	if (shell->cursor_array->size > 0 && get_parent(shell, 1) != NULL && get_parent(shell, 1)->type == CMD_JOIN)
		return (1);
	return (0);
}

void add_join(t_shell *shell)
{
	t_command *append_command;

	if (!on_join(shell))
	{
		append_command = malloc(sizeof(t_command));
		append_command->type = CMD_JOIN;
		append_command->content.array = ft_arr_new(10);
		ft_arr_append(shell->cursor, append_command);
		ft_arr_append(shell->cursor_array, shell->cursor);
		shell->cursor = append_command->content.array;
	}
}

void exit_join(t_shell *shell)
{
	if (on_join(shell))
		shell->cursor = ft_arr_pop(shell->cursor_array);
}

void append_quote(t_shell *shell)
{
	t_command *append_command;

	if (shell->command != NULL)
	{
		append_command = malloc(sizeof(t_command));
		append_command->type = CMD_TEXT;
		append_command->content.str = shell->command;
		ft_arr_append(shell->cursor, append_command);
		shell->command = NULL;
	}
}

int exit_quote(t_prompt_status *status)
{
	// printf("quote-A\n");
	if (status->squote + status->dquote > 1)
	{
		// printf("quote-B\n");
		status->squote = 0;
		status->dquote = 0;
		return (1);
	}
	return (0);
}

int	ms_parser(char *line, t_prompt_status *status, t_shell *shell)
{
	size_t		i;
	size_t		len;
	size_t		verif;
	t_type		type;
	t_command	*append_command;
    char    	*newline;

	i = 0;   
	verif = ft_strlen(line);
	if (verif <= 0)
		return (0);

	if (status->dquote || status->squote)
	{
		if (shell->command == NULL)
			shell->command = ft_strdup("\n");
		else
			shell->command = ft_strjoin(shell->command, ft_strdup("\n"));
	}
    if (shell->prompt_listen)
    {
        newline = shell->prompt;
        if (status->parenthesis)
		{
			if (status->print || status->parenthesis != status->last_parenthesis)
                shell->prompt = ft_strjoin_seperator(shell->prompt, line, "; ");
			else
				shell->prompt = ft_strjoin_seperator(shell->prompt, line, " ");
		}
		else if (status->newline)
		{
			status->newline = 0;
			shell->prompt = ft_strjoin_seperator(shell->prompt, line, " ");
		}
        else
            shell->prompt = ft_strjoin_seperator(shell->prompt, line, "\n");
        replace_history_entry(shell->line, shell->prompt, NULL);
        //Fonction utiliser en bonus
        free(newline);
    }
    shell->prompt_listen = 1;
	while (line[i])
	{
		type = get_type(&line[i]);
		if (type == E_EOF)
			break ;
		len = next_indent(type, &line[i]);
		if (type == E_METACHAR && get_metachar(&line[i]) == E_AND)
			type = E_WORD;
		// printf("A | %d\n", status->dquote);
        if (!status->squote && !status->dquote)
        {
			// printf("B | %d\n", status->dquote);
            if (type >= E_METACHAR && type <= E_OPERATOR && !is_chevron(type) && status->operator == 1 && !status->c_parenthesis)
			{
				// printf("C\n");
                ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
			}
            if (type >= E_PARENTHESIS && type <= E_OPERATOR && !is_chevron(type) && status->chevron == 1)
			{
				// printf("D\n");
                ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
			}
            if (is_chevron(type) && status->chevron == 1)
			{
				// printf("E\n");
                ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
			}
            if ((type == E_METACHAR || type == E_OPERATOR) && status->print == 0 && !status->c_parenthesis)
			{
				// printf("F | %d\n", status->print);
                ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
			}
            if (type == E_WORD || type == E_NAME)
            {
                status->print = 1;
                status->operator = 0;
				status->chevron = 0;
                status->newline = 0;
				status->no_empty = 1;
				status->c_parenthesis = 0;
            }

			if (type == E_HEREDOC)
			{
				status->heredoc = 1;
				status->no_empty = 1;
				status->print = 0;
			}

			if (status->heredoc && status->print)
			{
				shell->limiter = select_str(&line[i], len);
				if (add_fd(shell))
					return (0);
				while (1)
				{
					newline = readline("heredoc> ");
					if (!newline)
						break ;
					if (ft_strlen(shell->limiter) == ft_strlen(newline) && ft_strncmp(newline, shell->limiter, ft_strlen(shell->limiter)) == 0)
					{
						free(newline);
						break ;
					}
					write(
						((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1]), 
						newline, 
						ft_strlen(newline));
					write((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1], "\n", 1);
					free(newline);
				}
				write((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1], "\0", 1);
				close((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1]);
			}

            if (type > E_PARENTHESIS && type <= E_OPERATOR)
            {
				status->newline = 0;
                status->c_parenthesis = 0;
				status->print = 0;
                if (is_chevron(type))
                    status->chevron = 1;
                else
				{
					if (type == E_OPERATOR)
						status->newline = 1;
					else if (type == E_METACHAR && ft_strncmp(&line[i], "|", 1) == 0)
						status->newline = 1;
                    status->operator = 1;
				}
            }

            // if (type == E_NEWLINE)
            // {
            //     if (status->print == 0)
            //         ms_syntax_error(E_SYNTAX_UPD_EOF, NULL, shell);
            //     status->print = 0;
			// 	status->c_parenthesis = 0;
            // }

            if (type == E_COMMENT)
                break ;

            if (type == E_PARENTHESIS)
            {
				status->newline = 0;
				status->c_parenthesis = 0;
                if (ft_strncmp(&line[i], "(", 1) == 0)
                {
					if (on_join(shell))
						ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
					if(actual_cursor(shell) != NULL && actual_cursor(shell)->type == CMD_PARENTHESIS)
						ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
					status->parenthesis += 1;
					status->no_empty = 0;
					append_command = malloc(sizeof(t_command));
					append_command->type = CMD_PARENTHESIS;
					append_command->content.array = ft_arr_new(10);
					ft_arr_append(shell->cursor, append_command);
					ft_arr_append(shell->cursor_array, shell->cursor);
					shell->cursor = append_command->content.array;
					status->last_parenthesis = status->parenthesis;
				}
                else
                {
					status->c_parenthesis = 1;
                    if (status->parenthesis == 0 || status->operator || !status->no_empty)
                        ms_syntax_error(E_SYNTAX_UPD_TOK, select_str(&line[i],len), shell);
                    else
					{
						exit_join(shell);
						// status->no_empty = 0;
						status->last_parenthesis = status->parenthesis;
						if (shell->cursor_array->size > 0 && get_parent(shell, 1) != NULL && get_parent(shell, 1)->type != CMD_PARENTHESIS)
                        {
							shell->cursor = ft_arr_pop(shell->cursor_array);
							// ft_arr_pop(shell->cursor_array);
                        }
						shell->cursor = ft_arr_pop(shell->cursor_array);
                        status->parenthesis -= 1;
					}
                
                }
            }
        }

        if (type == E_SQUOTE  && !status->dquote)
            status->squote++;
        if (type == E_DQUOTE  && !status->squote)
            status->dquote++;

        if (status->squote + status->dquote > 1)
		{
			status->print = 1;
			status->operator = 0;
			status->no_empty = 1;
			status->newline = 0;
		}

        //end error
        if (shell->prompt_listen == 0)
            break ;
		if (DEBUG_MODE)
        	printf(C_YELLOW"%ld | type: %d | is: %s | p: %d\n", shell->cursor_array->size,  type, select_str(&line[i], len),  status->parenthesis);
		
		
		if (status-> print && status->heredoc)
		{
			add_join(shell);
			append_command = malloc(sizeof(t_command));
			append_command->type = CMD_HEREDOC;
			append_command->content.fd = (int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1];
			ft_arr_append(shell->cursor, append_command);
			// ft_arr_append(shell->commands, ft_strjoin("<< ",ft_itoa((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1])));
			status->heredoc = 0;
		}
		else if (type == E_NAME)
		{
			// printf("TEST : %dcommandsn", shell->cursor-);
			add_join(shell);
			append_quote(shell);
			append_command = malloc(sizeof(t_command));
			append_command->type = CMD_EXPAND;
			if (status->dquote)
				append_command->type = CMD_EXPAND_QUOTE;
			if (status->squote)
			{
				append_command->type = CMD_TEXT;
				append_command->content.str = select_str(&line[i], len);
			}
			else
				append_command->content.str = select_str(&line[i+1], len-1);
			ft_arr_append(shell->cursor, append_command);
		}
		else if (status->squote || status->dquote)
		{
			add_join(shell);
			if (type == E_SQUOTE || type == E_DQUOTE)
			{
				if (exit_quote(status))
					append_quote(shell);
			}
			else if (exit_quote(status))
			{
				if (shell->command == NULL)
					shell->command = ft_strdup(select_str(&line[i], len));
				else
					shell->command = ft_strjoin(shell->command, select_str(&line[i], len));
				append_quote(shell);
			}
			else if (shell->command == NULL)
			{
				shell->command = ft_strdup(select_str(&line[i], len));
			}
			else
			{
				shell->command = ft_strjoin(shell->command, select_str(&line[i], len));
			}
		}
		else if (type == E_REDIR_IN || type == E_REDIR_OUT || type == E_APPEND)
		{
			add_join(shell);
			append_command = malloc(sizeof(t_command));
			append_command->type = get_CMD(type, &line[i]);
			append_command->content.fd = 0;
			ft_arr_append(shell->cursor, append_command);
		}
		else if (type == E_WILDCARD)
		{
			add_join(shell);
			append_command = malloc(sizeof(t_command));
			append_command->type = CMD_WILDCARD;
			append_command->content.str = select_str(&line[i], len);
			ft_arr_append(shell->cursor, append_command);
		}
		else if (type == E_EMPTY) {
			//a voir
			if (on_join(shell))
			{
				append_command = malloc(sizeof(t_command));
				append_command->type = CMD_EMPTY;
				ft_arr_append(shell->cursor, append_command);
			}
			(void)"tkt frere";
		}
		else if(!status->heredoc && type != E_PARENTHESIS)
		{
			if(exit_quote(status))
				shell->command = ft_strjoin(shell->command, select_str(&line[i], len));
			append_quote(shell);
			append_command = malloc(sizeof(t_command));
			append_command->type = get_CMD(type, &line[i]);
			if (append_command->type == CMD_PIPE)
			{
				append_command = NULL;
				
				
				if (on_join(shell))
				{
					exit_join(shell);
					append_command = ft_arr_pop(shell->cursor);
				}
				else if (actual_cursor(shell)->type == CMD_PARENTHESIS)
				{
					append_command = ft_arr_pop(shell->cursor);
				}
				add_pipe(shell);
				if (append_command != NULL)
					ft_arr_append(shell->cursor, append_command);
			}
			else if (append_command->type == CMD_TEXT)
			{
				add_join(shell);
				append_command->content.str = select_str(&line[i], len);
				ft_arr_append(shell->cursor, append_command);
			}
			else
			{
				exit_join(shell);
				exit_pipe(shell);
				append_command->content.array = ft_arr_new(10);
				if (shell->cursor_array->size > 0 &&  get_parent(shell, 1) != NULL && get_parent(shell, 1)->type != CMD_PARENTHESIS)
					shell->cursor = ft_arr_pop(shell->cursor_array);
                ft_arr_append(shell->cursor_array, shell->cursor);
				shell->cursor = append_command->content.array;
				ft_arr_append(shell->cursor_array->data[shell->cursor_array->size - 1], append_command);
			}
		}
		i += len;
        len = 0;
	}
	
	
	// if(exit_quote(status))
	// 	shell->command = ft_strjoin(shell->command, select_str(&line[i], len));
	// append_quote(shell);
	
    if (status->chevron)
        ms_syntax_error(E_SYNTAX_UPD_NLN, NULL, shell);
    
    if (shell->prompt_listen == 0)
		return (0);
	
	// printf(" %d | %d | %d | %d | %d\n", status->heredoc, status->squote, status->dquote, status->parenthesis, status->newline);
    while (status->heredoc || status->squote || status->dquote || status->parenthesis || status->newline)
    {

		newline = readline("> ");
		if (!newline)
			break ;
		ms_parser(newline, status, shell);
		if (shell->prompt_listen == 0)
			break ;
		// free(newline);
    }
	if (DEBUG_MODE)
    	printf(C_BLUE"indent: "C_WHITE"%zu | %zu\n"C_RESET, i, verif);
	return (1);
}


char *CMD_to_str(t_command_type type)
{
	if (type == CMD_TEXT)
		return ("CMD_TEXT");
	if (type == CMD_EXPAND)
		return ("CMD_EXPAND");
	if (type == CMD_HEREDOC)
		return ("CMD_HEREDOC");
	if (type == CMD_REDIR_IN)
		return ("CMD_REDIR_IN");
	if (type == CMD_REDIR_OUT)
		return ("CMD_REDIR_OUT");
	if (type == CMD_APPEND)
		return ("CMD_APPEND");
	if (type == CMD_PIPE)
		return ("CMD_PIPE");
	if (type == CMD_PARENTHESIS)
		return ("CMD_PARENTHESIS");
	if (type == CMD_WILDCARD)
		return ("CMD_WILDCARD");
	if (type == CMD_EMPTY)
		return ("CMD_EMPTY");
	if (type == CMD_JOIN)
		return ("CMD_JOIN");
	if (type == CMD_AND)
		return ("CMD_AND");
	if (type == CMD_OR)
		return ("CMD_OR");
	if (type == CMD_EXPAND_QUOTE)
		return ("CMD_EXPAND_QUOTE");
	if (type == CMD_AND_IF)
		return ("CMD_AND_IF");
	if (type == CMD_SEMICOLON)
		return ("CMD_SEMICOLON");
	return ("CMD_UNKNOWN");
}

void print_indent(int indent)
{
	int i = 0;
	while (i < indent)
	{
		printf("\t");
		i++;
	}
}
void command_to_json(int indent, t_array *array)
{
	printf("[\n");
	while (array->size > 0)
	{
		t_command *command = (t_command *)array->data[0];
		print_indent(indent);
		printf("\t{\n");
		print_indent(indent);
		printf("\t\ttype : `%d-%s`,\n", command->type, CMD_to_str(command->type));
		if (!(command->type == CMD_WILDCARD || command->type == CMD_EMPTY))
		print_indent(indent);
		if (command->type == CMD_TEXT || command->type == CMD_EXPAND || command->type == CMD_EXPAND_QUOTE)
			printf("\t\tcontent : `%s`\n", command->content.str);
		else if (command->type == CMD_WILDCARD || command->type == CMD_EMPTY)
			(void)"tkt frere";
		else if (command->type == CMD_HEREDOC || command->type == CMD_REDIR_IN || command->type == CMD_REDIR_OUT || command->type == CMD_APPEND)
			printf("\t\tcontent : %d\n", command->content.fd);
		else if(command->content.array != NULL)
		{
			printf("\t\tcontent : ");
			command_to_json(indent + 2, command->content.array);
		}

		print_indent(indent);
		printf("\t},\n");

		// ft_arr_free((void *)command->content.array, 0);
		ft_arr_shift(array);
	}
	print_indent(indent);
	printf("]\n");
}

void command_map(t_array *array, void *(*f)(void *))
{
	ft_arr_map(array, (void *)f, 0);
}

void *print_json(t_command *command)
{

	printf("{");
	printf("type:`%d-%s`,", command->type, CMD_to_str(command->type));
	if (command->type == CMD_TEXT || command->type == CMD_EXPAND || command->type == CMD_EXPAND_QUOTE)
		printf("content:`%s`", command->content.str);
	else if (command->type == CMD_WILDCARD || command->type == CMD_EMPTY)
		(void)"tkt frere";
	else if (command->type == CMD_HEREDOC || command->type == CMD_REDIR_IN || command->type == CMD_REDIR_OUT || command->type == CMD_APPEND)
		printf("content:%d", command->content.fd);
	else if(command->content.array != NULL)
	{
		printf("content:[");
		command_map(command->content.array, (void *)print_json);
		printf("],");
	}

	printf("},");
	return (command);
}


/**
 * @brief Fonction qui va recupérer les commandes de l'utilisateur et les executer
 *
 * @param shell Structure principal du programme
 * @return int **0** si tout c'est bien passé sinon **1**
 */

//production
/**/

//fd[0] = read/input
//fd[1] = write/output
//todo ms_handle_join
//expand
//fd
//join
int	ms_handle_join(t_array *array, t_shell *shell, int fd[2])
{
	t_exec	    *exec_cmd;
	t_command	*command;
	char		*word;
	size_t	i;
	if (!shell->prompt_listen)
		return (0);

	exec_cmd = malloc(sizeof(t_exec));
	exec_cmd->content = ft_arr_new(20);
	exec_cmd->fd[0] = -1;
	exec_cmd->fd[1] = -1;

	word = NULL;
	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_TEXT)
		{
			if (!word)
				word = ft_strdup("");
			word = ft_strjoin(word, command->content.str);
		}
		else if (command->type == CMD_EXPAND || command->type == CMD_EXPAND_QUOTE)
		{
			if (word == NULL)
				word = ft_strdup("");

			//special
			if (!ft_strlen(command->content.str))
				word = ft_strjoin(word, "$");
			else
			{
				shell->command =  ms_env_get(shell->env,command->content.str);
				if (command->type != CMD_EXPAND_QUOTE)
				{
					if (shell->command != NULL && shell->command[0])
					{
						char	**temp_char;
						int		temp;
						
						temp = ft_include(" \t", shell->command[0]);
						
						temp_char = ft_split_chars(shell->command, " \t");
						if (*temp_char != NULL && !temp)
						{
							word = ft_strjoin(word, temp_char[0]);
							ft_arr_append(exec_cmd->content, word);
							word = NULL;
							temp_char++;
						}
						while (*temp_char != NULL)
						{
							if ((*(temp_char + 1)) != NULL)
								ft_arr_append(exec_cmd->content, temp_char);
							else
								word = *temp_char;
							temp_char++;
						}
					}
				}
				else if (shell->command != NULL)
					word = ft_strjoin(word, ft_strdup(shell->command));	
				shell->command = NULL;
			}
			
		}
		else if (command->type == CMD_EMPTY)
		{
			if (word != NULL)
				ft_arr_append(exec_cmd->content, word);
			word = NULL;
		}
		else if (command->type == CMD_HEREDOC)
		{
			if (exec_cmd->fd[0] != -1)
				close(exec_cmd->fd[0]);
			exec_cmd->fd[0] = command->content.fd;
		}
		else if (command->type == CMD_REDIR_IN)
		{
			if (exec_cmd->fd[0] != -1)
				close(exec_cmd->fd[0]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			exec_cmd->fd[0] = open(command->content.str, O_RDONLY);
		}
		else if (command->type == CMD_REDIR_OUT)
		{
			if (exec_cmd->fd[1] != -1)
				close(exec_cmd->fd[1]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			exec_cmd->fd[0] = open(command->content.str, O_CREAT | O_WRONLY);
		}
		else if (command->type == CMD_APPEND)
		{
			if (exec_cmd->fd[1] != -1)
				close(exec_cmd->fd[1]);
			i++;
			command = (t_command *)array->data[i];
			if (command->type == CMD_EMPTY)
				i++;
			command = (t_command *)array->data[i];
			//[TODO]faire gestion erreur expand | access...
			exec_cmd->fd[0] = open(command->content.str, O_CREAT | O_APPEND);
		}
		i++;
	}

	if (exec_cmd->fd[0] == -1)
		exec_cmd->fd[0] = fd[0];
	if (exec_cmd->fd[1] == -1)
		exec_cmd->fd[1] = fd[1];
		
	if (word != NULL)
		ft_arr_append(exec_cmd->content, word);
		
	if (DEBUG_MODE)
	{
		printf(C_YELLOW"FD: %d | %d\n"C_RESET, exec_cmd->fd[0], exec_cmd->fd[1]);
		while (exec_cmd->content->size > 0)
		{
			word = exec_cmd->content->data[0];
			printf("\n%s", word);
			ft_arr_shift(exec_cmd->content);
		}
	}
	
	

	if (DEBUG_MODE && exec_cmd->fd[0] != 0)
	{
		char *buffer = ft_calloc(sizeof(char), 10000);;
		read(exec_cmd->fd[0], buffer, 10000);
		printf(C_BLUE"%s\n"C_RESET, buffer);
		free(buffer);
	}
	printf("\n");
	return (1);
}

int	ms_handle_pipe(t_array *array, t_shell *shell, int fd[2])
{
	(void)array;
	(void)fd;
	if (!shell->prompt_listen)
		return (0);
	printf("PIPE...\n");
	return (1);
}

int ms_handle(t_array *array, t_shell *shell, int fd[2])
{
	printf("EXEC...\n");
	if (!shell->prompt_listen)
		return (0);
	size_t i;
	t_command *command;
	
	i = 0;
	while (i < array->size)
	{
		command = (t_command *)array->data[i];
		if (command->type == CMD_JOIN)
			ms_handle_join(command->content.array, shell, fd);
		else if (command->type == CMD_AND_IF && !shell->status)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_OR && shell->status)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_SEMICOLON)
			ms_handle(command->content.array, shell, fd);
		else if (command->type == CMD_PIPE)
			ms_handle_pipe(command->content.array, shell, fd);
		else if (command->type == CMD_PARENTHESIS)
			ms_handle(command->content.array, shell, fd);
		i++;
	}
	return (1);
}

int	ms_prompt(t_shell *shell)
{
	char			*line;
	t_prompt_status	status;

	shell->line = 0;
	shell->status = 0;
	while (1)
	{
        status = (t_prompt_status){0};
		line = readline(MS_NAME"$ ");
		shell->heredoc_fd = ft_arr_new(10);
		shell->heredoc_size = 0;
		shell->commands = ft_arr_new(10);
		shell->cursor = shell->commands;
		shell->cursor_array = ft_arr_new(10);
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
            shell->prompt_listen = 0;
			status = (t_prompt_status){0};
            shell->prompt = ft_strdup(line);
			ms_parser(line, &status, shell);
			if (shell->prompt_listen)
				ms_handle(shell->commands, shell, (int [2]){0, 1});
			if (DEBUG_MODE)
			{
            	printf(C_RED"%s\n"C_RESET, shell->prompt);
				printf(C_GREEN"FD: %d\n"C_RESET, shell->heredoc_size/2);
				printf("--------------------\n"C_GREEN"[");
				command_map(shell->commands, (void *)print_json);
				printf("]"C_RESET"\n--------------------\n");
				command_to_json(0, shell->commands);
				printf("\n--------------------\n");
			}
			
            shell->line++;
		}
		free(line);
	}
	return (0);
}
/**/

//dev tester
/*
int	ms_prompt(t_shell *shell)
{
	char			*line;
	t_prompt_status	status;

	shell->line = 0;
	
        status = (t_prompt_status){0};
	shell->heredoc_fd = ft_arr_new(10);
	shell->heredoc_size = 0;
	shell->commands = ft_arr_new(10);
	shell->cursor = shell->commands;
	shell->cursor_array = ft_arr_new(10);


	shell->prompt_listen = 0;
	status = (t_prompt_status){0};
	// line = ft_strdup("echo \"hello world\" | cat -e");
	// line = ft_strdup("test des pipes | truc ewdew | dewdwe fwe");
	// line = ft_strdup("test des jointyures $dedwdew-frefreq wdwe && dewwde wewe");
	// line = ft_strdup("test des parentheses classique(echo \"hello world\")");
	// line = ft_strdup("test des parentheses imbriquéesV1 (test1 && test2 && (test3) && test4) && test5");
	line = ft_strdup("test des parentheses imbriquéesV2 && A1 && (B1 && B2 && (C1 && C2 && (D1 && D2 || D3) && C3) && B3) && A2");
	shell->prompt = ft_strdup(line);
	ms_parser(line, &status, shell);
	if (DEBUG_MODE)
	{
		printf(C_RED"%s\n"C_RESET, shell->prompt);
		printf(C_GREEN"FD: %d\n"C_RESET, shell->heredoc_size/2);
		// print list heredoc
		int i = 0;
		while (shell->heredoc_size > 0 && i <= shell->heredoc_size/2)
		{
			printf(C_BLUE"- FD: %d | %d\n"C_RESET, (int)(intptr_t)shell->heredoc_fd->data[i], (int)(intptr_t)shell->heredoc_fd->data[i+1]);
			i+=2;
		}
		i = 0;
		while (shell->heredoc_size > 0 && i < shell->heredoc_size)
		{
			char *buffer = ft_calloc(sizeof(char), 100);
			ft_strcpy(buffer, "test");
			read((int)(intptr_t)shell->heredoc_fd->data[i], buffer, 100);
			printf(C_BLUE"%s\n"C_RESET, buffer);
			free(buffer);
			i += 2;
		}
		printf("--------------------\n");
		command_to_json(0, shell->commands);
		printf("\n--------------------\n");
	}
	free(line);
	return (0);
}
*/