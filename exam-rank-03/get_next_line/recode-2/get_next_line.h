#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define TRUE 1
# define FALSE 0

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_node;

char	*get_next_line(int fd);
void	add_node(t_node **lst, char *s);
int		read_to_list(int fd, t_node **lst);
char	*extract_line(t_node *lst, char **remainder);

size_t	ft_strlen(char const *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, size_t start, size_t len);
int		has_newline(const char *s);
void	free_list(t_node **lst);
#endif