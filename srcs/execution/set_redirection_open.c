/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:01:09 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:01:10 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "error.h"
#include <fcntl.h>

static void	set_redirection_open_in(t_node *redirct_nd, int *fd);
static void	set_redirection_open_out(t_node *redirct_nd, int *fd);
static void	set_redirection_open_outappend(t_node *redirct_nd, int *fd);
static void	set_redirection_open_heredoc(t_node *redirct_nd, int *fd);

int	set_redirection_type(t_node *redirct_nd, int *fd)
{
	if (ft_strncmp(redirct_nd->str1, "<", 2) == 0)
		set_redirection_open_in(redirct_nd, fd);
	else if (ft_strncmp(redirct_nd->str1, ">", 2) == 0)
		set_redirection_open_out(redirct_nd, fd);
	else if (ft_strncmp(redirct_nd->str1, ">>", 3) == 0)
		set_redirection_open_outappend(redirct_nd, fd);
	else if (ft_strncmp(redirct_nd->str1, "<<", 3) == 0)
		set_redirection_open_heredoc(redirct_nd, fd);
	else
		return (-1);
	return (1);
}

static void	set_redirection_open_in(t_node *redirct_nd, int *fd)
{
	if (fd[STD_IN] > 2)
		close2 (fd[STD_IN]);
	fd[STD_IN] = open(redirct_nd->str2[0], O_RDONLY);
	if (fd[STD_IN] == -1)
		exit (print_errno(fd[STD_ERROR], redirct_nd->str2[0], NULL, 1));
}

static void	set_redirection_open_out(t_node *redirct_nd, int *fd)
{
	if (fd[STD_OUT] > 2)
		close2 (fd[STD_OUT]);
	fd[STD_OUT] = open(redirct_nd->str2[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[STD_OUT] == -1)
		exit (print_errno(fd[STD_ERROR], redirct_nd->str2[0], NULL, 1));
}

static void	set_redirection_open_outappend(t_node *redirct_nd, int *fd)
{
	if (fd[STD_OUT] > 2)
		close2 (fd[STD_OUT]);
	fd[STD_OUT] = open(redirct_nd->str2[0], \
						O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[STD_OUT] == -1)
		exit (print_errno(fd[STD_ERROR], redirct_nd->str2[0], NULL, 1));
}

static void	set_redirection_open_heredoc(t_node *redirct_nd, int *fd)
{
	if (fd[STD_IN] > 2)
		close2 (fd[STD_IN]);
	fd[STD_IN] = open(redirct_nd->str2[0], O_RDONLY);
	if (fd[STD_IN] == -1)
		exit (print_errno(fd[STD_ERROR], redirct_nd->str2[0], NULL, 1));
	unlink(redirct_nd->str2[0]);
}
