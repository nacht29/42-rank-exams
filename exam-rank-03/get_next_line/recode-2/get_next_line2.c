#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	char	*ptr;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(total_len + 1);
	if (!ptr)
		return (NULL);
	joined = ptr;
	while (*s1)
	{
		*ptr = *s1;
		s1++;
		ptr++;
	}
	while (*s2)
	{
		*ptr = *s2;
		s2++;
		ptr++;
	}
	*ptr = '\0';
	return (joined);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

int		has_newline(const char *s)
{
	if (!s)
		return (FALSE);
	while (*s)
	{
		if (*s == '\n')
			return (TRUE);
		s++;
	}
	return (FALSE);
}

void	free_list(t_node **lst)
{
	t_node	*cur;
	t_node	*temp;

	if (!lst || !(*lst))
		return ;
	cur = *lst;
	while (cur)
	{
		temp = cur->next;
		free(cur->str);
		free(cur);
		cur = temp;
	}
	*lst = NULL;
}
