#include <stdio.h>

char to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c += 32);
	return (c);
}

char *produce_base(int base)
{
	char base_str[base + 1];
	char ref[16] = "0123456789abcdef";
	char *ret;

	for (int i = 0; i < base; i++)
		base_str[i] = ref[i];
	base_str[base] = '\0';
	ret = base_str;
	return (ret);
}

int get_digit(char c, char *base)
{
	int i = 0;

	while (base[i])
	{
		if (base[i] == c)
			break;
		i++;
	}
	return (i);
}

int calc(int digit, int base, int power)
{
	int og_base = base;
	if (power == 0)
		return (digit);
	for (int i = 1; i < power; i++)
		base *= og_base;
	return (digit * base);	
}

int ft_atoi_base(const char *str, int str_base)
{
	int 		base = str_base;
	int			result = 0;
	int			digit;
	int			power = 0;
	char		*base_str;
	const char	*start = str;		

	base_str = produce_base(base);
	while (*str)
		str++;
	str--;
	while (str != start - 1)
	{
		digit = get_digit(*str, base_str);
		result += calc(digit, base, power);
		power++;
		str--;
	}
	return (result);
}

int main(void)
{
	// for (int  i = 0; i <= 3; i++)
	// 	printf("power: %i %i\n", i, calc(1, 16, i));
	// printf("%s\n", produce_base(16));
	// printf("get_digit: %i", get_digit('1', produce_base(11)));
	int i = ft_atoi_base("23", 5);
	printf("final: %i\n", i);
}