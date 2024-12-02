#include <unistd.h>

char	to_upper(char c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int	is_alnum(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*str_cap(char *str)
{
	int		flag;
	char	*s;

	flag = 1;
	s = str;

    while (*s)
        s++;
	while (s != str - 1)
	{
		if (is_alnum(*s) == 1)
		{
			if (flag == 1)
			{
				*s = to_upper(*s);
				flag = 0;
			}
			else
				*s = to_lower(*s);
		}
		else
			flag = 1;
		s--;
	}
	return (str);
}

int main(int ac, char *av[])
{
	char    *s;

	if (ac > 1)
	{
		for (int i = 1; i < ac; i++)
		{
			s = str_cap(av[i]);
			while (*s)
			{
				write(1, s, 1);
				s++;
			}
			write(1, "\n", 1);
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}