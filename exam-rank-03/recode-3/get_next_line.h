#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# define TRUE 1
# define FALSE 0

typedef struct s_list
{
	char					*str;
	size_t					offset;
	size_t					remain;
	struct s_list	*next;
}	t_node;

char	*get_next_line(int fd);
void	add_node(t_node **lst, char *s);
int		read_to_list(int fd, t_node **lst);
char	*extract_lines(t_node *lst, char **temp_buff);
char	*process_newline_str(t_node *lst, char *line, char **temp_buff);
void	free_list(t_node **lst);

size_t	ft_strlen(char *s);
char	*ft_substr(char* s, size_t start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int		has_newline(char *s);

#endif
