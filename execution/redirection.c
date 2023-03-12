#include "minishell.h"
#include "execution.h"
#include "error.h"

int	redirection(t_node *redirct_nd, int *fd)
{
	if (fd == NULL || fd[STD_IN] == -1 || fd[STD_OUT] == -1)
		return (-1);
	if (set_redirection(redirct_nd, fd) == NULL)
		return (-1);
	if (fd[STD_IN] != STD_IN && dup2(fd[STD_IN], STD_IN) == -1)
		return (print_errno(STD_ERROR, "fail redirection", NULL, -1));
	if (fd[STD_OUT] != STD_OUT && dup2(fd[STD_OUT], STD_OUT) == -1)
		return (print_errno(STD_ERROR, "fail redirection", NULL, -1));
	if (fd[STD_ERROR] != STD_ERROR && dup2(fd[STD_ERROR], STD_ERROR) == -1)
		return (print_errno(STD_ERROR, "fail redirection", NULL, -1));
	return (1);
}

int	*set_redirection(t_node *redirct_nd, int *fd)
{
	while (redirct_nd)
	{
		if (set_redirection_type(redirct_nd, fd) == -1)
			return (NULL);
		redirct_nd = redirct_nd->left;
	}
	return (fd);
}
