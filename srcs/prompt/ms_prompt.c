/**
 * @file ms_prompt.c
 * @brief Fichier qui contient la fonction qui va lancer le prompt
 * 
 */

#include "char.h"
#include "conf.h"
#include "minishell.h"
#include "prompt.h"
#include <stdio.h>

int ms_syntax_error(t_error error, char *msg, t_shell *shell)
{
    // a replace
    (void) shell;
    // !a replace

    if (error == SYNTAX_UPD_TOK)
    {
        printf(ERR_SYNTAX_UPD_TOK, msg);
        free(msg);
    }
    else if (error == SYNTAX_UPD_EOF)
        printf(ERR_SYNTAX_UPD_EOF);
    else if (error == SYNTAX_UPD_NLN)
        printf(ERR_SYNTAX_UPD_NLN);
    shell->prompt_listen = 0;
    return (0);
}

int ft_include(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char *select_str(char *str, size_t n)
{
    char *new;
    size_t i;

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


//attention foret de IF!!!!
int ms_prompt_check_status(char *line, t_prompt_status *status, t_shell *shell)
{
    size_t i;
    size_t len;

    i = 0;
    len = ft_strlen(line);
    len--;
    shell->prompt_listen = 1;
    
    while (line[i])
    {

        if (line[i] == ' ' || line[i] == '\t')
            status->white = 1;
        else
            status->white = 0;

        if (ft_isalpha(line[i]) || ft_isdigit(line[i]))
        {
            if (!status->started && status->metachar)
                ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i-1], 1), shell);
            else if (!status->started && status->operator)
                ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i-3], 2), shell);
            status->metachar = 0;
            status->operator = 0;
            status->print = 1;
            status->started = 1;
            status->newline = 0;
        }

        if (line[i] == '\'' && !status->dquote)
        {
            status->metachar = 0;
            status->operator = 0;
            status->quote = !status->quote;
        }

        if (line[i] == '\"' && !status->quote)
        {
            status->metachar = 0;
            status->operator = 0;
            status->dquote = !status->dquote;
        }

        if (!status->quote && !status->dquote)
        {
            if(ft_include("()", line[i]))
            {
                if (!status->started && status->metachar)
                    ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i-1], 1), shell);
                else if (!status->started && status->operator)
                    ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i-3], 2), shell);
            }
            if (line[i] == '(' && (!status->print || ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 1), shell)))
            {
                status->parenthesis++;
                status->metachar = 0;
                status->operator = 0;
                status->print = 0;
            }

            else if (line[i] == ')' && ((status->parenthesis > 0 && status->print) || ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 1), shell)))
            {
                status->parenthesis--;
                status->metachar = 0;
                status->operator = 0;
            }

            else if (ft_include("|&;", line[i]) && status->operator)
                ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i-2], 2), shell);
            else if (!status->metachar && ft_include("|&;", line[i]) && (status->print || (i != len || ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 1), shell))) )
            {
                status->metachar = 1;
            }
            else if (status->metachar && ft_include("|&;", line[i]) && line[i] != line[i - 1] && ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i-1+status->started], 1), shell))
            {
                status->metachar = 0;
                status->operator = 0;
            }
            else if (status->metachar && ft_include("|&;", line[i]) && line[i] == line[i - 1])
            {
                status->metachar = 0;
                status->operator = 1;
            }

            if (!status->white && shell->prompt_listen && (status->operator || (status->metachar && len==i)) && (status->print || ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i-1], 2), shell)))
            {
                status->print = 0;
                status->operator = 0;
                status->metachar = 0;
                status->newline = 1;
            };

            if (line[i] == '>')
            {
                if (i == len)
                    ms_syntax_error(SYNTAX_UPD_NLN, NULL, shell);
                else if (ft_include(">\"\'\t ",line[i + 1] ) + ft_isalpha(line[i]) + ft_isdigit(line[i]) == 0)
                    ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 1), shell);
                status->started = 1;
                status->metachar = 1;
            }
        }

        if (!shell->prompt_listen)
            return (0);
        i++;
    }

    if (status->quote || status->parenthesis || status->dquote || status->newline)
    {
        shell->line = 1;
        return (0);
    }
    return (1);
    
}

/**
 * @brief Fonction qui va recupérer les commandes de l'utilisateur et les executer
 * 
 * @param shell Structure principal du programme
 * @return int **0** si tout c'est bien passé sinon **1**
 */
int ms_prompt(t_shell *shell)
{
    char *line;
    t_prompt_status status;


    status = (t_prompt_status) {0};

    shell->line = 0;
    while (1)
    {   
        if ( shell->line)
        {
            line = readline("> ");
        }
        else
            line = readline("minishell$ ");

        if (!line)
            break;
        if (line[0] != '\0')
            add_history(line);
        if (ms_prompt_check_status(line, &status, shell))
        {
            status = (t_prompt_status) {0};
            shell->line = 0;
        }
        else if (!shell->line)
            status = (t_prompt_status) {0};
        free(line);
    }
    return (0);
}