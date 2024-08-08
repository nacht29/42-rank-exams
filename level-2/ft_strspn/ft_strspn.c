#include <stdio.h>

char    *ft_strchr(char *str, int ref)
{
    while (*str)
    {
        if (*str == ref)
            return (str);
        str++;
    }
    return (NULL);
}

size_t  ft_strspn(const char *s, const char *accept)
{
    size_t  i;

    i = 0;
    while (s[i])
    {
        if (ft_strchr(accept, s[i]) == NULL)
            break;
        i++;
    }
    return (i);
}

int main(void)
{
    printf("%lu\n", ft_strspn("apple", "api"));
}