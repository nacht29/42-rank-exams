#include <unistd.h>
#include <stdio.h>

int ft_atoi(char *num)
{
	int count = 0;
	int op = 1;

	while(*num == ' ' || (*num >= 9 && *num <= 13))
		num++;
	if (*num == '+' || *num == '-')
	{
		if (*num == '-')
			op = -1;
		num++;
	}
	while (*num)
	{
		count = count * 10 + (*num - '0');
		num++;
	}
	return (count * op);
}

int is_prime(int num)
{
	int ref = num / 2;

	while (ref > 1)
	{
		if (num % ref == 0)
			return (0);
		ref--;
	}
	return (1);
}

void putnbr(int n)
{
	if (n > 1)
		putnbr(n / 10);
	char c = '0' + n % 10;
	write(1, &c, 1);
}

int main(int argc, char *argv[])
{
	int num = ft_atoi(argv[1]);
	int prime = 0;

	if (argc == 2 && num > 0)
	{
		while (num > 0)
		{
			if (is_prime(num) == 1)
				prime += num;
			num--;
		}
		putnbr(prime - 1);
	}
	else
		write(1, "0\n", 1);
}