#include "get_next_line.h"

/* int main(void)
{
	int	fd = open("text.txt", O_RDONLY);
	char *line;
	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// }
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
} */

char	*get_next_line(int fd)
{
	static  t_node	*lst;
	char			*next_line;
	char			*remainder;
	int				byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = NULL;
	byte_read = read_to_list(fd, &lst);
	if (byte_read < 0 || (byte_read == 0 && lst == NULL))
		return (NULL);
	next_line = extract_line(lst, &remainder);
	free_list(&lst);
	if (remainder != NULL)
	{
		add_node(&lst, remainder);
		free(remainder);
		remainder = NULL;
	}
	return (next_line);
}

void	add_node(t_node **lst, char *s)
{
	t_node	*new_node;
	t_node	*end;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->str = ft_strjoin("", s);
	new_node->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	end = *lst;
	while (end->next)
		end = end->next;
	end->next = new_node;
}

int		read_to_list(int fd, t_node **lst)
{
	int		byte_read;
	t_node	*cur;
	char	*buffer;

	while (1)
	{
		cur = *lst;
		while (cur)
		{
			if (has_newline(cur->str) == TRUE)
				return (1);
			cur = cur->next;
		}
		buffer = malloc(BUFFER_SIZE + 1);
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read <= 0)
		{
			free(buffer);
			return (byte_read);
		}
		buffer[byte_read] = '\0';
		add_node(lst, buffer);
		free(buffer);
	}
	return (byte_read);
}

char	*extract_line(t_node *lst, char **remainder)
{
	char	*line;
	char	*temp;
	char	*s1;
	size_t	i;

	line = malloc(1);
	line[0] = '\0';
	while (lst)
	{
		if (has_newline(lst->str) == FALSE)
		{
			temp = ft_strjoin(line, lst->str);
			free(line);
			line = temp;
		}
		else
		{
			i = 0;
			while (lst->str[i] != '\n')
				i++;
			s1 = ft_substr(lst->str, 0, i + 1);
			temp = ft_strjoin(line, s1);
			free(line);
			line = temp;
			free(s1);
			if (lst->str[i + 1] != '\0')
				*remainder = ft_substr(lst->str, i + 1, ft_strlen(lst->str) - (i + 1));
		}
		lst = lst->next;
	}
	return (line);
}

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
