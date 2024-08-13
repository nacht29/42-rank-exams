/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacht <nacht@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:11:19 by yachan            #+#    #+#             */
/*   Updated: 2024/08/14 01:54:53 by nacht            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static size_t	alloc_len(char const *s, char c);
static void	split(char const *s, char c, char ***str_arr, size_t itr);


static char	*ft_substr(const char *s, int start, size_t len)
{
	size_t	i;
	char	*holder = malloc(len + 1);

	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		holder[i] = s[start + i];
		i++;
	}
    holder[len] = '\0';
	return (holder);
}

/*
*splits str according to delimiter and store the splitted substr in an array
*return value: array of substr
*/
char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**str_arr;

	if (!s)
		return (NULL);
	len = alloc_len(s, c);
	str_arr = malloc((len + 1) * sizeof(char *));
	if (!str_arr)
		return (NULL);
	split(s, c, &str_arr, len);
	str_arr[len] = NULL;
	return (str_arr);
}

static size_t	alloc_len(char const *s, char c)
{
	size_t	len;
	int		flag;

	len = 0;
	flag = 1;
	while (*s)
	{
		if (*s != c && flag == 1)
		{
			len++;
			flag = 0;
		}
		else if (*s == c)
			flag = 1;
		s++;
	}
	return (len);
}

static void	split(char const *s, char c, char ***str_arr, size_t itr)
{
	size_t	start;
	size_t	end;
	size_t	arr_pos;

	start = 0;
	arr_pos = 0;
	while (itr > 0)
	{
		end = 0;
		while (s[start] == c)
			start++;
		while (s[start + end] != c && s[start + end] != '\0')
			end++;
		(*str_arr)[arr_pos] = ft_substr(s, (int)start, end);
		start = start + end;
		arr_pos++;
		itr--;
	}
}

int main(int ac, char *av[])
{
	char **s = ft_split(av[1], ' ');	

	int i = 0;
	int j;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			write(1, &s[i][j], 1);
			j++;
		}
		i++;
		if (s[i] != NULL)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}