#include "get_next_line.h"

int main(void)
{
	int	fd = open("text.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
}

char	*get_next_line(int fd)
{
	static t_node	*lst;
	int				byte_read;
	char			*next_line;
	char			*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = NULL;
	byte_read = read_to_list(fd, &lst);
	if (byte_read < 0 || (byte_read == 0 && lst == NULL))
		return (NULL);
	next_line = extract_lines(lst, &remainder);
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

int	read_to_list(int fd, t_node **lst)
{
	int		byte_read;
	char	*buffer;
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

char	*extract_lines(t_node *lst, char **remainder)
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
