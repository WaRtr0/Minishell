#include <stdlib.h>
#include <unistd.h>

char	*ft_select_str(char *str, size_t n)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (n + 1));
	if (!tmp)
		return (NULL);
	while (i < n)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
