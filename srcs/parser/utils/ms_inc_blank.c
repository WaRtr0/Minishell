#include "conf.h"
#include "utils.h"

int	ms_inc_blank(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_include(BLANK, str[i]))
		i++;
	return (i);
}
