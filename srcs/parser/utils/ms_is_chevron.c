#include "conf.h"
#include "parser.h"

int ms_is_chevron(t_type type)
{
	if (type == E_REDIR_IN
		|| type == E_REDIR_OUT
		|| type == E_APPEND
		|| type == E_HEREDOC)
		return (1);
    return (0);
}