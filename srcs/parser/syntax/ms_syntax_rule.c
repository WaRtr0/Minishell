#include "arr.h"
#include "char.h"
#include "conf.h"
#include "parser.h"
#include "str.h"
// #include "num.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "exec.h"
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>

int ms_syntax_rule(int type, char *str,t_shell *shell, t_prompt_status *status)
{
    if (status->no_print && (type == E_WORD || type == E_NAME || type == E_SQUOTE || type == E_DQUOTE) && !status->chevron)
        ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
    if (type >= E_METACHAR && type <= E_OPERATOR && !ms_is_chevron(type) && status->operator == 1 && !status->c_parenthesis)
        ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
    if (type >= E_PARENTHESIS && type <= E_OPERATOR && !ms_is_chevron(type) && status->chevron == 1)
        ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
    if (ms_is_chevron(type) && status->chevron == 1)
        ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);
    if ((type == E_METACHAR || type == E_OPERATOR) && status->print == 0 && !status->c_parenthesis)
        ms_syntax_error(E_SYNTAX_UPD_TOK, str, shell);

    if (shell->prompt_listen)
        return (0);
    return (1);
}