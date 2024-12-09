#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	void	*ptr;

	ptr = "hi";
	// ft_printf("%p\n", ptr);
	// printf("%p\n", ptr);
	// printf("len %i\n", ft_printf("%p\n", ptr));
	int i = printf("hi\n");
	// printf("%i\n", i);
}
