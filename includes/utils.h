#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif
# define MAX_FD 256

# define GNL_ERROR -1
# define GNL_EOF 0
# define GNL_EXIST 1

/*
** util.c
*/
void	safe_free(char **ptr);
/*
** get_line.c
*/
int		get_next_line(int fd, char **line);

#endif