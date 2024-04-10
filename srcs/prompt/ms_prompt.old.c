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

int ms_prompt_check_status(char *line, t_prompt_status *status, t_shell *shell)
{
    size_t i;
    size_t len;
    i = 0;
    if (shell->col != 0)
    {
        printf("PROMPT : %s\n", line);
        i = shell->col;
        shell->col = 0;
    }
    len = ft_strlen(line);
    len--;
    if (len <= 0)
        return (0);
    shell->prompt_listen = 1;
    while (line[i])
    {
        if (line[i] == ' ' || line[i] == '\t')
            status->white += 1;

        if (status->heredoc && status->print && !(ft_isalpha(line[i]) || ft_isdigit(line[i])))
        {
            shell->col = i;
            shell->limiter = select_str(&line[i - status->print], status->print);
            status->heredoc = 1;
            shell->line = 1;
            printf(RED "DEBUGC :" GREEN "\n{\nstop : %lu,\nquote : %d,\ndquote : %d,\nparenthesis : %d,\nmetachar : %d,\noperator : %d,\nwhite : %d,\nnewline : %d,\nchevron : %d,\nappend : %d,\nheredoc : %d,\nprint : %d,\nstarted : %d\n}\n" RESET, i, status->quote, status->dquote, status->parenthesis, status->metachar, status->operator, status->white, status->newline, status->chevron, status->append, status->heredoc, status->print, status->started);
            return (2);
        }

        if (ft_isalpha(line[i]) || ft_isdigit(line[i]))
        {
            if (!status->started && status->metachar)
                ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i - 1], 1), shell);
            else if (!status->started && status->operator)
                ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i - 3], 2), shell);
            status->metachar = 0;
            status->operator = 0;
            status->append = 0;
            status->white = 0;
            status->chevron = 0;
            status->print += 1;
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
            if (ft_include(PARENTHESIS, line[i]))
            {
                if (!status->started && status->metachar)
                    ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i - 1], 1), shell);
                else if (!status->started && status->operator)
                    ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i - 3], 2), shell);
            }
            if (ft_include(METACHAR, line[i]))
            {
                if (line[i] == '(' && (!status->print || ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 1), shell)))
                {
                    status->parenthesis++;
                    status->metachar = 0;
                    status->white = 0;
                    status->operator = 0;
                    status->print = 0;
                }
                else if (line[i] == ')' && ((status->parenthesis > 0 && status->print) || ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 1), shell)))
                {
                    status->parenthesis--;
                    status->metachar = 0;
                    status->white = 0;
                    status->operator = 0;
                    status->newline = 0;
                }
                else if (status->heredoc || status->append || (status->chevron && status->white && !status->started))
                {
                    if (len != i && line[i] == line[i + 1])
                        ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 2), shell);
                    ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 1), shell);
                }
                else if (!status->metachar && !status->print && i == len)
                {
                    if (ft_include(CHEVRON, line[i]))
                        ms_syntax_error(SYNTAX_UPD_NLN, NULL, shell);
                    ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i], 1), shell);
                }
                else if (status->metachar && !status->print && line[i] != line[i - 1])
                    ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i - 1 + status->started], 1), shell);
                else if (!status->metachar && !status->chevron)
                {
                    if (ft_include(CHEVRON, line[i]))
                        status->chevron += 1;
                    else
                        status->metachar = 1;
                }
                else if ((status->metachar || status->chevron) && line[i] == line[i - 1])
                {
                    if (line[i] == '>')
                    {
                        status->append = 1;
                        status->chevron = 0;
                    }
                    else if (line[i] == '<')
                    {
                        status->heredoc = 1;
                        status->chevron = 0;
                    }
                    else
                    {
                        status->metachar = 0;
                        status->operator = 1;
                    }
                    status->white = 0;
                }
            }
            if (!status->white && (status->operator || (status->metachar && len == i)))
            {
                if (status->print)
                {
                    status->print = 0;
                    if (status->operator || (status->metachar && !ft_include(";&", line[i])))
                        status->newline = 1;
                    status->operator = 0;
                    status->metachar = 0;
                }
                else
                {
                    if (ft_include(CHEVRON, line[i]))
                    {
                        ms_syntax_error(SYNTAX_UPD_NLN, NULL, shell);
                    }
                    else
                    {
                        ms_syntax_error(SYNTAX_UPD_TOK, select_str(&line[i - 1], 2), shell);
                    }
                }
            }
        }
        if (!shell->prompt_listen)
        {
            printf(RED "DEBUGA :" GREEN "\n{\nstop : %lu,\nquote : %d,\ndquote : %d,\nparenthesis : %d,\nmetachar : %d,\noperator : %d,\nwhite : %d,\nnewline : %d,\nchevron : %d,\nappend : %d,\nheredoc : %d,\nprint : %d,\nstarted : %d\n}\n" RESET, i, status->quote, status->dquote, status->parenthesis, status->metachar, status->operator, status->white, status->newline, status->chevron, status->append, status->heredoc, status->print, status->started);
            return (0);
        }
        i++;
    }
    if (status->heredoc && status->print && !(ft_isalpha(line[i]) || ft_isdigit(line[i])))
    {
        shell->col = i;
        shell->limiter = select_str(&line[i - status->print], status->print);
        status->heredoc = 1;
        shell->line = 1;
        printf(RED "DEBUGC :" GREEN "\n{\nstop : %lu,\nquote : %d,\ndquote : %d,\nparenthesis : %d,\nmetachar : %d,\noperator : %d,\nwhite : %d,\nnewline : %d,\nchevron : %d,\nappend : %d,\nheredoc : %d,\nprint : %d,\nstarted : %d\n}\n" RESET, i, status->quote, status->dquote, status->parenthesis, status->metachar, status->operator, status->white, status->newline, status->chevron, status->append, status->heredoc, status->print, status->started);
        return (2);
    }
    printf(RED "DEBUGB :" GREEN "\n" BOLD "{\nquote : %d,\ndquote : %d,\nparenthesis : %d,\nmetachar : %d,\noperator : %d,\nwhite : %d,\nnewline : %d,\nchevron : %d,\nappend : %d,\nheredoc : %d,\nprint : %d,\nstarted : %d\n}\n" RESET, status->quote, status->dquote, status->parenthesis, status->metachar, status->operator, status->white, status->newline, status->chevron, status->append, status->heredoc, status->print, status->started);
    if (status->quote || status->parenthesis || status->dquote || status->newline)
    {
        shell->line = 1;
        return (0);
    }
    if (status->append || status->heredoc || status->chevron)
    {
        ms_syntax_error(SYNTAX_UPD_NLN, NULL, shell);
        return (0);
    }
    return (1);
}



int ms_add_heredoc(t_shell *shell)
{
    int fds[2];

    if (!shell->limiter)
        return (1);

    // create pipe

    pipe(fds);

    if (shell->heredoc_size == 0)
        shell->heredoc_fd = ft_arr_new(2);
    shell->heredoc_size += 1;
    ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fds[0]);
    ft_arr_append(shell->heredoc_fd, (void *)(intptr_t)fds[1]);
    return (0);
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
    char *cache;
    char *tmp;
    int response;
    t_prompt_status status;
    cache = ft_strdup("");
    status = (t_prompt_status){0};
    shell->line = 0;
    while (1)
    {
        
        if (shell->line && (!shell->col || status.heredoc))
            line = readline("> ");
        else if (!shell->col)
            line = readline("minishell$ ");
        else
        {
            line = shell->prompt;
            shell->prompt = NULL;
        }

        
        if (!status.heredoc)
        {
            tmp = cache;
            cache = ft_strjoin(tmp, line);
            free(tmp);
            response = ms_prompt_check_status(line, &status, shell);

            if (response == 1)
            {
                status = (t_prompt_status){0};
                shell->line = 0;
            }
            else if (response == 2)
            {
                printf("HEREDOC!!!\n name : %s\n", shell->limiter);
                ms_add_heredoc(shell);
                shell->prompt = line;
                printf("HEREDOC CREATED SIZE : %d, FD_OUTPUT : %d, FD_INPUT : %d\n", shell->heredoc_size, (int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 2], (int)(intptr_t)shell->heredoc_fd->data[shell->heredoc_size - 1]);
            }
            else if (!shell->line)
                status = (t_prompt_status){0};

            if (!shell->line && cache[0] != '\0')
            {
                add_history(cache);
                free(cache);
                cache = ft_strdup("");
            }
        }
        else {
            if (ft_strlen(shell->limiter) == ft_strlen(line ) && ft_strncmp(line, shell->limiter, ft_strlen(shell->limiter)) == 0)
            {
                status = (t_prompt_status){0};
                shell->line = 0;
                free(shell->limiter);
                shell->limiter = NULL;
            }
            else
            {
                tmp = cache;
                cache = ft_strjoin(tmp, line);
                free(tmp);
                tmp = cache;
                cache = ft_strjoin(tmp, "\n");
                free(tmp);
            }
        }
        free(line);
    }
    return (0);
}