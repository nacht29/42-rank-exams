/*
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static char	*process_newline_str(t_node *lst, char **temp_buff, char *line);

char	*get_next_line(int fd)
{
	static t_node	*lst = NULL;
	char			*next_line;
	char			*temp_buff = NULL;
	int				read_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((read_result = read_to_list(&lst, fd)) <= 0)
	{
		free_list(&lst);
		return (NULL);
	}
	next_line = extract_line(lst, &temp_buff);
	free_list(&lst);
	if (temp_buff != NULL)
	{
		add_node(&lst, temp_buff);
		free(temp_buff);
	}
	return (next_line);
}

void	add_node(t_node **lst, char *str)
{
	t_node	*new_node;
	t_node	*end;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->str = str;
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

int	read_to_list(t_node **lst, int fd)
{
	char	*str;
	int		byte_read;

	while (1)
	{
		t_node *cur = *lst;
		while (cur)
		{
			if (has_newline(cur->str))
				return (1);
			cur = cur->next;
		}
		str = malloc(BUFFER_SIZE + 1);
		if (!str)
			return (-1);
		byte_read = read(fd, str, BUFFER_SIZE);
		if (byte_read <= 0)
		{
			free(str);
			return (byte_read);
		}
		str[byte_read] = '\0';
		add_node(lst, str);
	}
}

char	*extract_line(t_node *lst, char **temp_buff)
{
	char	*line = NULL;
	char	*temp;

	while (lst)
	{
		if (!has_newline(lst->str))
		{
			line = process_newline_str(lst, temp_buff, line);
			break;
		}
		temp = ft_strjoin(line, lst->str);
		free(line);
		line = temp;
		lst = lst->next;
	}
	return (line);
}

static char	*process_newline_str(t_node *lst, char **temp_buff, char *line)
{
	char	*new_line;
	char	*temp;
	size_t	i = 0;

	while (lst->str[i] != '\n' && lst->str[i] != '\0')
		i++;
	temp = ft_substr(lst->str, 0, i + 1);
	new_line = ft_strjoin(line, temp);
	free(line);
	free(temp);
	if (lst->str[i] != '\0')
		*temp_buff = ft_substr(lst->str, i + 1, ft_strlen(lst->str) - (i + 1));
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
	*lst = NULL;
}

int	has_newline(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	len = 0;

	while (s[len])
		len++;
	return (len);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*substr;
	size_t	i = 0;

	if (!s || start >= ft_strlen(s))
		return (NULL);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i = 0, j = 0;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int	main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	char	*line;

	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
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
	(*lst) = NULL;
}
*/

