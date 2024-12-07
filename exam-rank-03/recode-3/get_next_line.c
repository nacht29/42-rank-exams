#include "get_next_line.h"

int	main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s", line);
}

char	*get_next_line(int fd)
{
	static t_node	*lst = NULL;
	char			*next_line;
	char			*temp_buff;

	temp_buff = NULL;
	read_to_list(fd, &lst);
	next_line = extract_lines(lst, &temp_buff);
	free_list(&lst);
	if (temp_buff != NULL)
		add_node(&lst, temp_buff);
	free(temp_buff);
	return (next_line);
}

void	add_node(t_node **lst, char *s)
{
	t_node	*new_node;
	t_node	*end;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->str = ft_strjoin("", s);
	new_node->remain = ft_strlen(s);
	new_node->next = NULL;
	end = *lst;
	if (end == NULL)
	{
		*lst = new_node;
		return ;
	}
	while (end->next)
		end = end->next;
	end->next = new_node;
}

int	read_to_list(int fd, t_node **lst)
{
	char	*buffer;
	int		byte_read;
	t_node	*cur;

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
		if (byte_read <= 0 && buffer != NULL)
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

char	*extract_lines(t_node *lst, char **temp_buff)
{
	char	*line;
	char	*temp;

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
			line = process_newline_str(lst, line, temp_buff);
			return (line);
		}
		lst = lst->next;
	}
	return (line);
}

char	*process_newline_str(t_node *lst, char *line, char **temp_buff)
{
	char	*temp;
	char	*new_line;
	size_t	i;

	i = 0;
	while (lst->str[i] != '\n')
		i++;
	temp = ft_substr(line, 0, i + 1);
	new_line = ft_strjoin(line, temp);
	free(line);
	free(temp);
	if (lst->str[i + 1] != '\0')
		(*temp_buff) = ft_substr(lst->str, i + 1, ft_strlen(lst->str) - (i + 1));
	return (new_line);
}

void	free_list(t_node **lst)
{
	t_node	*cur;
	t_node	*temp;

	cur = *lst;
	while (cur)
	{
		temp = cur->next;
		free(cur->str);
		free(cur);
		cur = temp;
	}
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_substr(char* s, size_t start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	substr = malloc(len + 1);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*big_str;
	size_t	total_len;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	big_str = malloc(total_len);
	i = 0;
	while (*s1)
	{
		big_str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		big_str[i] = *s2;
		s2++;
		i++;
	}
	big_str[total_len - 1] = '\0';
	return (big_str); 
}

int	has_newline(char *s)
{
	if (!s)
		return (FALSE);
	while (*s)
	{
		if (*s == '\n')
			return (FALSE);
		s++;
	}
	return (TRUE);
}
