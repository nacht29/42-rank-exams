#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i])
		{
			if (argv[1][i] >= 65 && argv[1][i] <= 90)
				j = ((int)(argv[1][i]) - 65) + 1;
			else if (argv[1][i] >= 97 && argv[1][i] <= 122)
				j = ((int)(argv[1][i]) - 97) + 1;
			else
				j = 1;
			while (j > 0)
			{
				write(1, &argv[1][i], 1);
				j--;
			}
			i++;
		}
	}
	write(1, "\n", 1);
}
