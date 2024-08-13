#include <unistd.h>
#include <stdio.h>

/*
void reverse_bits(unsigned char octet)
{
	int i = 8;
	unsigned char 	bit;

	while (i--)
	{
		bit = (octet >> i & 1) + '0';
        if (bit == '1')
		    write(1, "0", 1);
        else
            write(1, "1", 1);
	}
}
*/

unsigned char	reverse_bits_og(unsigned char octet)
{
	int		i = 8;
	unsigned char	res = 0;

	while (i > 0)
	{
		res = res * 2 + (octet % 2);
		octet = octet / 2;
		i--;
	}
	return (res);
}

int main(void)
{
    // reverse_bits(25);
	printf("og: %d\n", reverse_bits_og(3));
}