#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "conf.h"
#include "str.h"
#include "utils.h"

int	ms_parser(char *line, t_prompt_s *status, t_shell *shell)
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
		type = ms_get_type(&line[i]);
		if (type == E_EOF)
			break ;
		len = ms_get_indent(type, &line[i]);
		if (type == E_METACHAR && ms_get_metachar(&line[i]) == E_AND)
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
			status->heredoc = 0;
		}
		else if (type == E_NAME)
		{
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
			append_command->type = ms_get_cmd(type, &line[i]);
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
		}
		else if(!status->heredoc && type != E_PARENTHESIS)
		{
			if(ms_reset_quote(status))
				shell->command = ft_strjoin(shell->command, ft_select_str(&line[i], len));
			ms_append_quote(shell);
			append_command = malloc(sizeof(t_command));
			append_command->type = ms_get_cmd(type, &line[i]);
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