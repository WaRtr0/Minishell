#ifndef UTILS_H
#  define UTILS_H

# include "str.h"
# include "unistd.h"
# include "stdlib.h"

char	*ft_select_str(char *str, size_t n);
int	ft_include(char const *str, char c);
char	**ft_split_chars(char const *s, char *c);
char *ft_strjoin_seperator(char *s1, char *s2, char *sep);

#endif