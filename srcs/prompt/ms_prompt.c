/**
 * @file ms_prompt.c
 * @brief Fichier qui contient la fonction qui va lancer le prompt
 * 
 */

#include "minishell.h"
#include "prompt.h"

int ms_prompt(t_shell *shell)
{
    char *line;
    (void) shell;
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            break;
        free(line);
    }
    return (0);
}