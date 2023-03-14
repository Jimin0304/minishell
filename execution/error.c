#include "minishell.h"
#include "execution.h"
#include "error.h"
#include <sys/errno.h>

int	print_error(int fd, char *str1, char *str2, int rtn)
{
	ft_putstr_fd("minishell: ", fd);
	if (str1 != NULL)
		ft_putstr_fd(str1, fd);
	if (str2 != NULL)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(str2, fd);
	}
	ft_putstr_fd("\n", fd);
	return (rtn);
}

int	print_errno(int fd, char *str1, char *str2, int rtn)
{
	char	*errno_str;

	errno_str = strerror(errno);
	ft_putstr_fd("minishell: ", fd);
	if (str1 != NULL)
	{
		ft_putstr_fd(str1, fd);
		ft_putstr_fd(": ", fd);
	}
	if (str2 != NULL)
	{
		ft_putstr_fd(str2, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(errno_str, fd);
	ft_putstr_fd("\n", fd);
	return (rtn);
}
