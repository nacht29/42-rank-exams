#include <unistd.h>

int main(int argc, char *argv[])
{
	int	i;

	i = -1;
	if (argc == 2)
	{
		while (argv[1][++i])
		{
			if ((argv[1][i] >= 65 && argv[1][i] <= 90) || (argv[1][i] >= 97 && argv[1][i] <= 122))
			{
				if (argv[1][i] == 90 || argv[1][i] == 122)
					argv[1][i] -= 25;
				else
					argv[1][i] += 1;
			}
			write(1, &argv[1][i], 1);
		}
	}
	write(1, "\n", 1);
}
