#include "gnl.h"

static char	*process_newline_str(t_node *lst, char **temp_buff, char *line);

char	*get_next_line(int fd)
{
	static t_node	*lst;
	char			*next_line;
	char			*temp_buff;
	int				read_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp_buff = NULL;
	if ((read_result = read_to_list(&lst, fd)) <= 0)
		return (NULL);
	next_line = extract_line(lst, &temp_buff);
	free_list(&lst);
	if (temp_buff != NULL)
	{
		add_node(&lst, temp_buff);
		free(temp_buff);
	}
	free_list(&lst);
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
	t_node	*cur;
	char	*str;
	int		byte_read;

	while (1)
	{
		cur = *lst;
		while (cur)
		{
			if (has_newline(cur->str) == False)
				return (1);
			cur = cur->next;
		}
		str = malloc(BUFFER_SIZE + 1);
		byte_read = read(fd, str, BUFFER_SIZE);
		if (byte_read <= 0)
		{
			free(str);
			return (byte_read);
		}
		str[byte_read] = '\0';
		add_node(lst, str);
		free(str);
	}
}

char	*extract_line(t_node *lst, char **temp_buff)
{
	char	*line;
	char	*temp;

	line = malloc(1);
	line[0] = '\0';
	while (lst)
	{
		if (has_newline(lst->str) == True)
		{
			temp = ft_strjoin(line, lst->str);
			line = temp;
			free(temp);
		}
		else
		{
			line = process_newline_str(lst, temp_buff, line);
			return (line);
		}
		lst = lst->next;
	}
	return (line);
}

static char	*process_newline_str(t_node *lst, char **temp_buff, char *line)
{
	char	*new_line;
	char	*temp;
	size_t	i;

	i = 0;
	while(lst->str[i] != '\n')
		i++;
	temp = ft_substr(lst->str, 0, i + 1);
	new_line = ft_strjoin(line, temp);
	free(line);
	free(temp);
	if (lst->str[i + 1] != 0)
		*temp_buff = ft_substr(lst->str, (i + 1), (ft_strlen(lst->str) - (i + 1)));
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


int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s\n", line);
}
