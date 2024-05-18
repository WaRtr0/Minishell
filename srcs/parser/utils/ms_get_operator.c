#include "conf.h"
#include "parser.h"

int	ms_get_operator(char *str)
{
	if (!ft_strncmp(str, S_OR, ft_strlen(S_OR)))
		return (E_OR);
	if (!ft_strncmp(str, S_AND_IF, ft_strlen(S_AND_IF)))
		return (E_AND_IF);
	return (-1);
}
