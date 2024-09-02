#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

int	ft_strchr(char *s, char ref)
{
	while (*s)
	{
		if (*s == ref)
			return (1);
		s++;
	}
	return (0);
}

int	base_to_num(char *base_str, char ref, int base)
{
	int	digit;

	digit = 0;
	while (base_str[digit])
	{
		if (base_str[digit] == ref)
			return (digit);
		digit++;
	}
	return (0);
}

int	ft_atoi_base(char *num, char *base)
{
	int	op;
	int	mult;
	int	results;

	op =  1;
	mult =  ft_strlen(base); 
	results = 0;
	while (*num == ' ' || (*num >= 9 && *num <= 32))
		num++;
	if (*num == '+' || op == '-')
	{
		if (*num == '-')
			op = -1;
		num++;
	}
	while (ft_strchr(base, *num) == 1)
	{
		results = results * mult + base_to_num(base, *num, mult);
		num++;
	}
	return (results);
}

int main(void)
{
	int i = ft_atoi_base("GA", "ABCDEFG");
	printf("%i\n", i);
}