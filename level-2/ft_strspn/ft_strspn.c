#include <stdio.h>
#include <string.h>

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

int main(int ac, char *av[])
{
	printf("og: %ld\n", strspn(av[1],av[2]));
	printf("%ld\n", ft_strspn(av[1],av[2]));
}