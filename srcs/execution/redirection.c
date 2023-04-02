/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:00:55 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:00:55 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "error.h"

static int ft_dup2(int *fd);

int	redirection(t_node *redirct_nd, int *fd)
{
	if (fd == NULL || fd[STD_IN] == -1 || fd[STD_OUT] == -1)
		return (-1);
	if (set_redirection(redirct_nd, fd) == NULL)
		return (-1);
	if (ft_dup2(fd) == -1)//여기서 파이프와 프로그램의 표준입력 및 출력을 연결
		return (-1);
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

static int ft_dup2(int *fd)
{
	if (fd[STD_IN] != STD_IN && dup2(fd[STD_IN], STD_IN) == -1)//fd[STD_IN]은 파이프의 출구이고 표준입력을 대체함
		return (print_errno(STD_ERROR, "fail redirection", NULL, -1));
	if (fd[STD_OUT] != STD_OUT && dup2(fd[STD_OUT], STD_OUT) == -1)//fd[STD_OUT]은 파이프의 입구이고 표준출력을 대체함
		return (print_errno(STD_ERROR, "fail redirection", NULL, -1));
	if (fd[STD_ERROR] != STD_ERROR && dup2(fd[STD_ERROR], STD_ERROR) == -1)
		return (print_errno(STD_ERROR, "fail redirection", NULL, -1));
	return (0);
}


