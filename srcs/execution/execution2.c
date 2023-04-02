/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:00:49 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 11:36:34 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "signal2.h"
#include "error.h"

static void	set_connect_pipein(t_node *pipe_nd, int *pipe_fd, int *fd);
static void	set_connect_pipeout(t_node *pipe_nd, int *pipe_fd, int *fd);

int	execution_wait_child(int *pids)
{
	int	i;
	int	statloc;
	int	exit_status;

	i = 0;
	exit_status = 1;
	if (pids[i] == 0)
		return (exit_status);
	while (pids[i])
	{
		if (pids[i] == -1)
			exit_status = -1;
		waitpid(pids[i], &statloc, 0);
		i++;
	}
	if (exit_status == -1)
		return (1);
	check_fork_signal(statloc);
	exit_status = check_exit_status(statloc);
	return (exit_status);
}

pid_t	*execution_fork(t_node *pipe_nd, char **env_path, pid_t *pids)
{
	int	i;
	int	pipe_fd[2];
	int	*fd;

	i = 0;
	init_fd(&fd);
	while (pipe_nd)//파이프 노드개수만큼 반목문을 실행
	{
		set_connect_pipein(pipe_nd, pipe_fd, fd);//출력을 파이프입구로 연결해두고
		set_signal_fork();
		pids[i] = fork();
		if (pids[i] == -1)
			print_errno(STD_ERROR, "fail execution_fork", NULL, 1);
		if (pids[i++] == 0)//자식프로세스 파트
		{
			if (pipe_nd->right)//파이프가 존재하면 파이프의 출구는 닫아둔다.어차피
				close2(pipe_fd[PIPE_OUT]);
			exit(execute_cmd(pipe_nd->left, fd, env_path));
		}
		set_connect_pipeout(pipe_nd, pipe_fd, fd);//입력을 파이프이 출구로 연결
		pipe_nd = pipe_nd->right;
	}
	free (fd);
	return (pids);
}

static void	set_connect_pipein(t_node *pipe_nd, int *pipe_fd, int *fd)
{
	if (pipe_nd->right)//파이프 노드가 오른쪽에 존재하면
	{
		if (pipe(pipe_fd) == -1)//파이프 생성하고
		{
			print_errno(STD_ERROR, "execution", NULL, -1);
			pipe_fd[STD_IN] = -1;
			pipe_fd[STD_OUT] = -1;
		}
		fd[STD_OUT] = pipe_fd[PIPE_IN];
	}
	else
		fd[STD_OUT] = STD_OUT;
}

static void	set_connect_pipeout(t_node *pipe_nd, int *pipe_fd, int *fd)
{
	if (fd[STD_IN] > 2)
		close2(fd[STD_IN]);
	if (pipe_nd->right)
	{
		fd[STD_IN] = pipe_fd[PIPE_OUT];
		close2(fd[STD_OUT]);
	}
}
