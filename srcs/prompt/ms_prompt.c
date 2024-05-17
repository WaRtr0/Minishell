/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by mmorot            #+#    #+#             */
/*   Updated: 2024/05/17 08:10:06 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ms_prompt.c
 * @brief Fichier qui contient la fonction qui va lancer le prompt
 *
 */
#include "arr.h"
#include "char.h"
#include "parser.h"
#include "conf.h"
#include "minishell.h"
#include "prompt.h"
#include "handle.h"
#include "lexer.h"
#include "str.h"
// #include "num.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "exec.h"
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "utils.h"
#include "debug.h"

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
	if (str[i] && str[i] == '?')
		return (2);
	while (str[i] && (ft_isdigit(str[i]) || ft_isalpha(str[i]) || ft_include("_", str[i])))
		i++;
	return (i);
}


t_type	get_type(char *str)
{
	const t_rule	rule[] = {{R_NOT_INC, NO_WORD, E_WORD},
	{R_INC, BLANK, E_EMPTY}, {R_INC, PARENTHESIS, E_PARENTHESIS},
	{R_OPER, NULL, E_OPERATOR}, {R_META, NULL, E_METACHAR},
	{R_CMP, S_DQUOTE, E_DQUOTE}, {R_CMP, S_SQUOTE, E_SQUOTE},
	{R_CMP, S_HEREDOC, E_HEREDOC}, {R_CMP, S_APPEND, E_APPEND},
	{R_CMP, S_REDIR_OUT, E_REDIR_OUT}, {R_CMP, S_REDIR_IN, E_REDIR_IN},
	{R_CMP, S_WILDCARD, E_WILDCARD}, {R_CMP, S_NEWLINE, E_NEWLINE},
	{R_CMP, S_DOLLAR, E_NAME}, {R_STOP, NULL, E_EOF}};
	size_t			i;

	i = 0;
	while (!(rule[i].type == R_STOP
		|| (rule[i].type == R_NOT_INC && !ft_include(rule[i].str, str[0]))
		|| (rule[i].type == R_INC && ft_include(rule[i].str, str[0]))
		|| (rule[i].type == R_OPER && get_operator(str) != -1)
		|| (rule[i].type == R_META && get_metachar(str) != -1)
		|| (rule[i].type == R_CMP && !ft_strncmp(str, rule[i].str,
				strlen(rule[i].str)))))
		{
			printf("%ld\n", i);
			i++;
		}
	return (rule[i].value);
}

int	next_indent(t_type value, char *str)
{
	if (value >= E_HEREDOC && value <= E_OPERATOR)
		return (2);
	if ((value >= E_DQUOTE && value <= E_REDIR_IN) || value == E_WILDCARD)
		return (1);
	if (value == E_WORD)
		return (pass_word(str));
	if (value == E_NAME)
		return (pass_name(str));
	if (value == E_EMPTY)
		return (pass_blank(str));
	return (-1);
}
	
int ms_is_chevron(t_type type)
{
    if (type == E_REDIR_IN || type == E_REDIR_OUT || type == E_APPEND || type == E_HEREDOC)
        return (1);
    return (0);
}

int ms_is_semicolon(t_type type, char *line)
{
	if (type == E_METACHAR && ft_strncmp(line, ";", 1) == 0)
		return (1);
	return (0);
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
		// a Enlever !
        replace_history_entry(shell->line, shell->prompt, NULL);
        //Fonction utiliser en bonus
        free(newline);
    }
    shell->prompt_listen = 1;
	status->no_print = 0;
	while (line[i])
	{

		// parsing
		type = get_type(&line[i]);
		if (type == E_EOF)
			break ;
		len = next_indent(type, &line[i]);
		if (type == E_METACHAR && get_metachar(&line[i]) == E_AND)
			type = E_WORD;
		if ((type == E_SQUOTE && status->dquote) || (type == E_DQUOTE && status->squote))
			type = E_WORD;

        if (!status->squote && !status->dquote)
        {
			ms_syntax_rule(type, ft_select_str(&line[i], len), shell, status);

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
				ms_heredoc(shell, ft_select_str(&line[i], len));

            if (type > E_PARENTHESIS && type <= E_OPERATOR)
            {
				status->newline = 0;
                status->c_parenthesis = 0;
				status->print = 0;
                if (ms_is_chevron(type))
                    status->chevron = 1;
                else
				{
					if (type == E_OPERATOR)
						status->newline = 1;
					else if (type == E_METACHAR && ft_strncmp(&line[i], "|", 1) == 0)
						status->newline = 1;
                    status->operator = 1;
					status->no_print = 0;
				}
            }

            // if (type == E_NEWLINE)
            // {
            //     if (status->print == 0)
            //         ms_syntax_error(E_SYNTAX_UPD_EOF, NULL, shell);
            //     status->print = 0;
			// 	status->c_parenthesis = 0;
            // }

            if (type == E_PARENTHESIS)
            {

				//semi parsing et lexing
				status->newline = 0;
				status->no_print = 0;
                if (ft_strncmp(&line[i], "(", 1) == 0)
                {
					if ((ms_get_parent(shell, 1) != NULL && ms_get_parent(shell, 1)->type == CMD_PIPE) && status->c_parenthesis && (ms_get_cursor(shell) != NULL && ms_get_cursor(shell)->type == CMD_PARENTHESIS))
						ms_syntax_error(E_SYNTAX_UPD_TOK, ft_select_str(&line[i],len), shell);
					if (ms_is_join(shell))
						ms_syntax_error(E_SYNTAX_UPD_TOK, ft_select_str(&line[i],len), shell);
					if(ms_get_cursor(shell) != NULL && ms_get_cursor(shell)->type == CMD_PARENTHESIS && !(ms_get_parent(shell, 1) != NULL && ms_get_parent(shell, 1)->type == CMD_PIPE))
					{
						printf("Y");
						ms_syntax_error(E_SYNTAX_UPD_TOK, ft_select_str(&line[i],len), shell);
					}
					status->c_parenthesis = 0;
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
                    if ((status->parenthesis == 0 || status->operator || !status->no_empty) && (ms_get_cursor(shell) != NULL && ms_get_cursor(shell)->type != CMD_SEMICOLON))
					{
						ms_syntax_error(E_SYNTAX_UPD_TOK, ft_select_str(&line[i],len), shell);
					}
                    else
					{
						ms_exit_join(shell);
						// status->no_empty = 0;
						status->last_parenthesis = status->parenthesis;
						if (shell->cursor_array->size > 0 && ms_get_parent(shell, 1) != NULL && ms_get_parent(shell, 1)->type != CMD_PARENTHESIS)
                        {
							shell->cursor = ft_arr_pop(shell->cursor_array);
							// ft_arr_pop(shell->cursor_array);
                        }
						shell->cursor = ft_arr_pop(shell->cursor_array);
                        status->parenthesis -= 1;
						status->no_print = 1;
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
			//check
			status->chevron = 0;
			status->no_empty = 1;
			status->newline = 0;
		}

        //end error

		//lexing 
        if (shell->prompt_listen == 0)
            break ;
		if (DEBUG_MODE)
        	printf(C_YELLOW"%ld | type: %d | is: %s | p: %d\n", shell->cursor_array->size,  type, ft_select_str(&line[i], len),  status->parenthesis);
		
		
		if (status-> print && status->heredoc)
		{
			if (status->no_print)
				ms_add_join(shell, CMD_JOIN_NO_PRINT);
			else
				ms_add_join(shell, -1);
			append_command = malloc(sizeof(t_command));
			append_command->type = CMD_HEREDOC;
			append_command->content.fd = (int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 2];
			ft_arr_append(shell->cursor, append_command);
			// ft_arr_append(shell->commands, ft_strjoin("<< ",ft_itoa((int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1])));
			status->heredoc = 0;
		}
		else if (type == E_NAME)
		{
			// printf("TEST : %dcommandsn", shell->cursor-);
			ms_add_join(shell, -1);
			ms_append_quote(shell);
			append_command = malloc(sizeof(t_command));
			append_command->type = CMD_EXPAND;
			if (status->dquote)
				append_command->type = CMD_EXPAND_QUOTE;
			if (status->squote)
			{
				append_command->type = CMD_TEXT;
				append_command->content.str = ft_select_str(&line[i], len);
			}
			else
				append_command->content.str = ft_select_str(&line[i+1], len-1);
			ft_arr_append(shell->cursor, append_command);
		}
		else if (status->squote || status->dquote)
		{
			ms_add_join(shell, -1);
			if (type == E_SQUOTE || type == E_DQUOTE)
			{
				if (ms_reset_quote(status))
				{
					if (shell->command == NULL)
						shell->command = ft_strdup("");
					ms_append_quote(shell);
				}
			}
			else if (ms_reset_quote(status))
			{
				if (shell->command == NULL)
					shell->command = ft_strdup("");
				shell->command = ft_strjoin(shell->command, ft_select_str(&line[i], len));
				ms_append_quote(shell);
			}
			else if (shell->command == NULL)
			{
				shell->command = ft_strdup(ft_select_str(&line[i], len));
			}
			else
			{
				shell->command = ft_strjoin(shell->command, ft_select_str(&line[i], len));
			}
		}
		else if (type == E_REDIR_IN || type == E_REDIR_OUT || type == E_APPEND)
		{
			if (status->no_print)
				ms_add_join(shell, CMD_JOIN_NO_PRINT);
			else
				ms_add_join(shell, -1);
			append_command = malloc(sizeof(t_command));
			append_command->type = get_CMD(type, &line[i]);
			append_command->content.fd = 0;
			ft_arr_append(shell->cursor, append_command);
		}
		else if (type == E_WILDCARD)
		{
			ms_add_join(shell, -1);
			append_command = malloc(sizeof(t_command));
			append_command->type = CMD_WILDCARD;
			append_command->content.str = ft_select_str(&line[i], len);
			ft_arr_append(shell->cursor, append_command);
		}
		else if (type == E_EMPTY) {
			//a voir
			if (ms_is_join(shell))
			{
				append_command = malloc(sizeof(t_command));
				append_command->type = CMD_EMPTY;
				ft_arr_append(shell->cursor, append_command);
			}
			(void)"tkt frere";
		}
		else if(!status->heredoc && type != E_PARENTHESIS)
		{
			if(ms_reset_quote(status))
				shell->command = ft_strjoin(shell->command, ft_select_str(&line[i], len));
			ms_append_quote(shell);
			append_command = malloc(sizeof(t_command));
			append_command->type = get_CMD(type, &line[i]);
			if (append_command->type == CMD_PIPE)
			{
				append_command = NULL;
				
				
				if (ms_is_join(shell))
				{
					ms_exit_join(shell);
					append_command = ft_arr_pop(shell->cursor);
				}
				else if (ms_get_cursor(shell)->type == CMD_PARENTHESIS)
				{
					append_command = ft_arr_pop(shell->cursor);
				}
				ms_add_pipeline(shell);
				if (append_command != NULL)
					ft_arr_append(shell->cursor, append_command);
			}
			else if (append_command->type == CMD_TEXT)
			{
				ms_add_join(shell, -1);
				append_command->content.str = ft_select_str(&line[i], len);
				ft_arr_append(shell->cursor, append_command);
			}
			else
			{
				ms_exit_join(shell);
				ms_exit_pipeline(shell);
				append_command->content.array = ft_arr_new(10);
				if (shell->cursor_array->size > 0 &&  ms_get_parent(shell, 1) != NULL && ms_get_parent(shell, 1)->type != CMD_PARENTHESIS)
					shell->cursor = ft_arr_pop(shell->cursor_array);
                ft_arr_append(shell->cursor_array, shell->cursor);
				shell->cursor = append_command->content.array;
				ft_arr_append(shell->cursor_array->data[shell->cursor_array->size - 1], append_command);
			}
		}
		i += len;
        len = 0;
	}
	
	
	// if(ms_reset_quote(status))
	// 	shell->command = ft_strjoin(shell->command, ft_select_str(&line[i], len));
	// ms_append_quote(shell);
	
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


int	ms_prompt(t_shell *shell)
{
	char			*line;
	t_prompt_status	status;

	shell->line = 0;
	shell->status = 0;
	shell->arb_pipe = 0;
    shell->in_pipe = 0;
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
            	ms_debug(shell);
			
            shell->line++;
		}
		free(line);
	}
	return (0);
}
