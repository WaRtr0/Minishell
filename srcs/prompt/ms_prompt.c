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
#include <stdio.h>
#include <stdlib.h>

int ms_syntax_error(t_error error, char *msg, t_shell *shell)
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

int get_operator(char *str)
{
    if (!ft_strncmp(str, S_OR, ft_strlen(S_OR) - 1))
        return (E_OR);
    if (!ft_strncmp(str, S_AND_IF, ft_strlen(S_AND_IF) - 1))
        return (E_AND_IF);
    if (!ft_strncmp(str, S_AND, ft_strlen(S_AND) - 1))
        return (E_AND);
    if (!ft_strncmp(str, S_PIPE, ft_strlen(S_PIPE) - 1))
        return (E_PIPE);
    if (!ft_strncmp(str, S_SEMICOLON, ft_strlen(S_SEMICOLON) - 1))
        return (E_SEMICOLON);
    return (-1);
}

int pass_blank(const char *str)
{
    size_t i;
    i = 0;
    while (str[i] && ft_include(BLANK, str[i]))
        i++;
    return (i);
}

int pass_word(const char *str)
{
    size_t i;
    i = 0;
    while (str[i] && !ft_include(NO_WORD, str[i]))
        i++;
    return (i);
}



int get_type(char *str)
{
    if (!ft_include(NO_WORD, str[0]))
        return (E_WORD);
    if (ft_include(BLANK, str[0]))
        return (E_EMPTY);
    if (get_operator(str) != -1)
        return (E_OPERATOR);
    if (!ft_strncmp(str, S_DQUOTE, ft_strlen(S_DQUOTE) - 1))
        return (E_DQUOTE);
    if (!ft_strncmp(str, S_SQUOTE, ft_strlen(S_SQUOTE) - 1))
        return (E_SQUOTE);
    if (!ft_strncmp(str, S_HEREDOC, ft_strlen(S_HEREDOC) - 1))
        return (E_HEREDOC);
    if (!ft_strncmp(str, S_APPEND, ft_strlen(S_APPEND) - 1))
        return (E_APPEND);
    if (!ft_strncmp(str, S_REDIR_OUT, ft_strlen(S_REDIR_OUT) - 1))
        return (E_REDIR_OUT);
    if (!ft_strncmp(str, S_REDIR_IN, ft_strlen(S_REDIR_IN) - 1))
        return (E_REDIR_IN);
    if (!ft_strncmp(str, S_COMMENT, ft_strlen(S_COMMENT) - 1))
        return (E_COMMENT);
    if (!ft_strncmp(str, S_WILDCARD, ft_strlen(S_WILDCARD) - 1))
        return (E_WILDCARD);
    if (!ft_strncmp(str, S_NEWLINE, ft_strlen(S_NEWLINE) - 1))
        return (E_NEWLINE);
    return (EOF);
}

int ms_parser(char *line, t_prompt_status *status, t_shell *shell)
{
    size_t i;
    size_t len;
    i = 0;
   
    len = ft_strlen(line);
    len--;
    if (len <= 0)
        return (0);
    shell->prompt_listen = 1;
    while (line[i])
    {
        
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
   
    status = (t_prompt_status){0};
    shell->line = 0;
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            break;
        if (line[0] != '\0')
        {
            add_history(line);
            ms_parser(line, &status, shell);
        }
        free(line);
    }
    return (0);
}