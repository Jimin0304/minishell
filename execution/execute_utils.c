#include "minishell.h"
#include "execution.h"
#include "error.h"


int	exit_status(int statloc)
{
	if ((statloc & 255) == 0)
		return ((statloc >> 8) & 255);
	return ((statloc & 127) + 128);
}

int	init_fd(int **fd)
{
	if (fd == NULL)
		return (-1);
	(*fd) = safe_ft_calloc(3, sizeof(int), "fail init fd");
	(*fd)[0] = STD_IN;
	(*fd)[1] = STD_OUT;
	(*fd)[2] = STD_ERROR;
	return (1);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		print_errno(STD_ERROR, NULL, NULL, 1);
}
