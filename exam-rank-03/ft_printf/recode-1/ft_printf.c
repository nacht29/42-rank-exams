#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#ifdef __APPLE__
# define NULL_STR "(null)"
#elif __linux__
# define NULL_STR ""
#else
# error "Unsupported OS"
#endif

int		ft_printf(const char *c, ...);
int		valid_form_spec(const char *c);
int		process_format(const char *c, int i, va_list arg);
size_t	ft_strlen(const char *s);
int		putstr(const char *s);
int		putnbr(int n);
int		puthex(unsigned int num);

int main(void)
{
	char *s = "hello world";
	int hex = 234;
	int num = 1657;

	// printf("testing: %s %x %d %% test complete\n", s, hex, num);
	ft_printf("testing: %s %x %d %% test complete\n", s, hex, num);
}

int	ft_printf(const char *c, ...)
{
	va_list	arg;
	int		i;
	int		count;

	if (valid_form_spec(c) == FALSE)
		return (0);
	i = 0;
	count = 0;
	va_start(arg, c);
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

int	valid_form_spec(const char *c)
{
	int		i;
	int		j;
	char	*valid_form;

	i = 0;
	valid_form = "dsx%%";
	while (c[i])
	{
		if (c[i] == '%')
		{
			j = 0;
			while (valid_form[j] && valid_form[j] != c[i + 1])
			{
				if (!valid_form[j])
					return (FALSE);
				j++;
			}
		}
		i++;
	}
	return (TRUE);
}

int	process_format(const char *c, int i, va_list arg)
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
		count += putstr("%%");
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

int	putstr(const char *s)
{
	if (!s)
	{
		write(1, NULL_STR, ft_strlen(NULL_STR));
		return ((int)ft_strlen(NULL_STR));
	}
	write(1, s, ft_strlen(s));
	return ((int)ft_strlen(s));
}

int	putnbr(int n)
{
	long	lnum;
	int		count;
	char	num;

	count = 0;
	lnum = n;
	if (n < 0)
	{
		lnum *= -1;
		write(1, "-", 1);
		count++;
	}
	if (n >= 10)
		count += putnbr(n / 10);
	count++;
	num = '0' + lnum % 10;
	write(1, &num, 1);
	return (count);
}

int	puthex(unsigned int num)
{
	long	lnum;
	char	n;
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	lnum = num;
	if (lnum >= 16)
		count += puthex(num / 16);
	n = base[num % 16];
	write(1, &n, 1);
	count++;
	return (count);
}
