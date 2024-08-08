#include <unistd.h>

int	is_dup(char *str, char c, int i)
{
	int	dup;

	dup = 0;
	while (str[dup])
	{
		if (str[dup] == c)
			break;
		dup++;
	}
	if (dup != i)
		return (0);
	return (1);
}

int main(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			j = 0;
			while (argv[2][j])
			{
				if (argv[2][j] == argv[1][i] && is_dup(argv[1], argv[1][i], i) == 1)
				{
					write(1, &argv[1][i], 1);
					break;
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
}