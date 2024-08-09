#include <unistd.h>

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

int main(void)
{
    reverse_bits(25);
}