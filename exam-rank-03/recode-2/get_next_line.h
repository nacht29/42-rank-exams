#ifndef GNL
# define GNL

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <stdlib.h> //malloc
# include <unistd.h> // read 
# include <fcntl.h> // open function
# include <stdio.h>

# define True 1
# define False 0

typedef struct s_linked_list
{
	char					*str;
	struct s_linked_list	*next;
}	t_node;

char	*get_next_line(int fd);
int		read_to_list(t_node **lst, int fd);
void	add_node(t_node **lst, char *buffer);
char	*extract_line(t_node *lst, char **temp_buff);
void	free_list(t_node **lst);

size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		has_newline(char *s);
char	*ft_substr(char *s, size_t start, size_t len);
char	*ft_strtrim(char *s1, char *set);
void	free_list(t_node **lst);

#endif