#include "get_next_line.h"

static char	*process_newline_node(t_node *lst, char **temp_buff, char *line);

int main(void)
{
	int	fd = open("test.txt", O_RDONLY);
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
	char			*temp_buff;
	char			*next_line;
	int				read_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp_buff = NULL;
	read_result = read_to_list(&lst, fd);
	if (read_result < 0 || (read_result == 0 && lst == NULL))
		return (NULL);
	next_line = extract_line(lst, &temp_buff);
	free_list(&lst);
	if (temp_buff != NULL)
	{
		add_node(&lst, temp_buff);
		free(temp_buff);
	}
	return (next_line);
}

/*
*goes thru the linked list to see if any nodes contain newline
	- return if node contain newline
	- keep reading until the next newline

*reads BUFFER_SIZE characters into buffer and store buffer as a 
new node in the linked list
*/
int	read_to_list(t_node **lst, int fd)
{
	int		char_read;
	char	*buffer;
	t_node	*current;

	while (1)
	{
		current = *lst;
		while (current)
		{
			if (ft_strchr(current->str, '\n'))
				return (1);
			current = current->next;
		}
		buffer = malloc(BUFFER_SIZE + 1);
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buffer);
			return (char_read);
		}
		buffer[char_read] = '\0';
		add_node(lst, buffer);
		free(buffer);
	}
}

/*
*strjoin is used in place of strdup because of function limit
(strjoin is reused multiple times in this project)
*
*malloc a node and duplicate buffer using strjoin
store the buffer into new node
*
*if list is empty save new node as first node
*else save new node as last node
*/
void	add_node(t_node **lst, char *buffer)
{
	t_node	*new_node;
	t_node	*end;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->str = ft_strjoin("", buffer);
	new_node->next = NULL;
	end = *lst;
	if (end == NULL)
	{
		*lst = new_node;
		return ;
	}
	while (end->next != NULL)
		end = end->next;
	end->next = new_node;
}

/*
*traverses linked list
*
*if str in node has no newline, join it into line
*
*else:
	-create 2 substr: next_line and remainder
	-next_line is extracted until the first newline
	-remainder is stored in a temporaty buffer
*
*in the main function:
	-static linked list is freed
	-remainder is stored into the first node (if there is a remainder)
*/
char	*extract_line(t_node *lst, char **temp_buff)
{
	char	*line;
	char	*temp;

	line = malloc(1);
	line[0] = '\0';
	while (lst)
	{
		if (ft_strchr(lst->str, '\n') == FALSE)
		{
			temp = ft_strjoin(line, lst->str);
			free(line);
			line = temp;
		}
		else
		{
			line = process_newline_node(lst, temp_buff, line);
			return (line);
		}
		lst = lst->next;
	}
	return (line);
}

/*
*part of extract line function, where node contains str with newline
*
*calculates the index of first newline
*
*creates a substr until the first newline (temp)
*join the substr to the main str (new_line = strjoin(temp, line))
*
*to store remainder into temp_buffer:
	-use substr
	-starting position = i + 1 (i is the index of newline)
	-length = len(full str) - starting_index + 1 (because index starts at 0)
	-check notes for demo
*/
static char	*process_newline_node(t_node *lst, char **temp_buff, char *line)
{
	size_t	i;
	char	*temp;
	char	*new_line;

	i = 0;
	while (lst->str[i] != '\n')
		i++;
	temp = ft_substr(lst->str, 0, i + 1);
	new_line = ft_strjoin(line, temp);
	free(line);
	free(temp);
	if ((lst->str)[i + 1] != '\0')
		*temp_buff = ft_substr(lst->str, (i + 1), (ft_strlen(lst->str) - (i + 1)));
	return (new_line);
}
