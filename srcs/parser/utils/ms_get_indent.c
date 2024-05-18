#include "conf.h"
#include "parser.h"

int	ms_get_indent(t_type value, char *str)
{
	if (value >= E_HEREDOC && value <= E_OPERATOR)
		return (2);
	if ((value >= E_DQUOTE && value <= E_REDIR_IN) || value == E_WILDCARD)
		return (1);
	if (value == E_WORD)
		return (ms_inc_word(str));
	if (value == E_NAME)
		return (ms_inc_name(str));
	if (value == E_EMPTY)
		return (ms_inc_blank(str));
	return (-1);
}