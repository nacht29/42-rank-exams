#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#ifdef __APPLE__
# define NULLS_STR "(null)"
#elif __linux__
# define NULL_STR ""
#else
# error "Unsupported OS"
#endif

#define TRUE 1
#define FALSE 0

int		ft_printf(const char *c, ...);
int		valid_form(const char *c);
int		process_format(const char *c, int i, va_list arg);
size_t	ft_strlen(const char *s);
int		putstr(const char *s);
int		putnbr(int n);
int		puthex(unsigned int num);

int main(void)
{
	char *s = "hello world";
	int hex = 234;
	int num = -1657;

	int i1;
	int i2;

	i1 = ft_printf("testing: %s %x %d %% test complete\n", s, hex, num);
	i2 = printf("testing: %s %x %d %% test complete\n", s, hex, num);
	// printf("%d\n", ft_printf("testing: %s %x %d %% test complete\n", s, hex, num));
	// printf("og: %d\n", printf("testing: %s %x %d %% test complete\n", s, hex, num));
	printf("1: %i 2: %i\n", i1, i2);
}

int		ft_printf(const char *c, ...)
{
	va_list	arg;
	int		i;
	int		count;

	if (valid_form(c) == FALSE)
		return (0);
	va_start(arg, c);
	i = 0;
	count = 0;
	while (c[i])
	{
		if (c[i] == '%')
		{
			count += process_format(c, i, arg);
			i++;
		}
		else
		{
			write(1, &c[i], 1);
			count++;
		}
		i++;
	}
	va_end(arg);
	return (count);
}

int		valid_form(const char *c)
{
	char	*valid;
	int		i;
	int		j;

	i = 0;
	valid = "dsx%%";
	while (c[i])
	{
		if (c[i] == '%')
		{
			j = 0;
			while (valid[j] && valid[j] != c[i + 1])
			{
				if (!valid[j])
					return (FALSE);
				j++;
			}
		}
		i++;
	}
	return (TRUE);
}

int		process_format(const char *c, int i, va_list arg)
{
	int	count;

	count = 0;
	if (c[i + 1] == 'd')
		count += putnbr(va_arg(arg, int));
	else if (c[i + 1] == 's')
		count += putstr(va_arg(arg, const char *));
	else if (c[i + 1] == 'x')
		count += puthex(va_arg(arg, int));
	else if (c[i + 1] == '%')
	{
		write(1, "%", 1);
		count++;
	}
	return (count);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int		putstr(const char *s)
{
	if (!s)
	{
		write(1, s, ft_strlen(NULL_STR));
		return ((int)ft_strlen(NULL_STR));
	}
	write (1, s, ft_strlen(s));
	return ((int)ft_strlen(s));
}

int	putnbr(int n)
{
	long	lnum;
	char	num;
	int		count;

	count = 0;
	lnum = n;
	if (n < 0)
	{
		lnum *= -1;
		write(1, "-", 1);
		count++;
	}
	if (lnum >= 10)
		count += putnbr(lnum / 10);
	count++;
	num = '0' + lnum % 10;
	write(1, &num, 1);
	return (count);
}

int	puthex(unsigned int num)
{
	int		count;
	long	lnum;
	char	*base;
	char	n;

	base = "0123456789abcdef";
	count  = 0;
	lnum = num;
	if (lnum >= 16)
		count += puthex(lnum / 16);
	n = base[num % 16];
	write(1, &n, 1);
	count++;
	return (count);
}
