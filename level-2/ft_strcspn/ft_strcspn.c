#include <stdio.h>

/*
*strcspn = find index of first similiar char - strps when current char in s is in reject
*strspn = find index of first diff char - stop if current char in s is not in accept
*/
size_t  ft_strcspn(const char *s, const char *reject)
{
	int	i = 0;
	int	j = 0;

	while (s[i] != '\0')
	{
	j = 0;
		while (reject[j] != '\0')
		{
			if(s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int main(void)
{
	printf("%ld\n", ft_strcspn("apple", "le"));
}