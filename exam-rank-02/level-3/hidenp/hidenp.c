#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	int j;

	if (argc == 3)
	{
		i = 0;
		j = 0;
		while (argv[1][i])
		{
			while (argv[2][j] && ( argv[2][j] != argv[1][i]))
				j++;
			if (!argv[2][j])
			{
				write(1, "0\n", 2);
				return (0);
			}
			i++;
		}
		write(1, "1", 1);
	}
	write(1, "\n", 1);
}