#ifndef ERROR_H
# define ERROR_H

//# include "libft.h"
# include <sys/stat.h>
# include <errno.h>


int		print_errno(int fd, char *str1, char *str2, int rtn);
int		print_error(int fd, char *str1, char *str2, int rtn);

#endif
