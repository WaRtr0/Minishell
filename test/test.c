#include <stdio.h>

int ft_strcmp(char *s1, char *s2)
{
    size_t i;
    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (1);
        i++;
    }
    if (s1[i] != s2[i])
        return (1);
    return (0);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    i = 0;
    while (s1[i] && s2[i] && i < n)
    {
        if (s1[i] != s2[i])
            return (1);
        i++;
    }
    if (s1[i] != s2[i])
        return (1);
    return (0);
}

int ft_strlen(const char *str)
{
    int i;
    i = 0;
    while (str[i])
        i++;
    return (i);
}

int main()
{
    printf("%i",ft_strlen("&&")-1);
}