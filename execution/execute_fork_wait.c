#include "execution.h"
#include "minishell.h"
#include "error.h"

static void	connect_pipe1(t_node *pipe_nd, int *pipe_fd, int *fd);
static void	connect_pipe2(t_node *pipe_nd, int *pipe_fd, int *fd);

int	execute_wait_child(int *pids)
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
		if (pids[i] == -1)//자식프로세스 중에 오류가 있을때
			exit_status = -1;
		waitpid(pids[i], &statloc, 0);
		i++;
	}
	if (exit_status == -1)
		return (1);
	check_fork_signal(statloc);
	exit_status = get_exit_status(statloc);
	return (exit_status);
}

pid_t	*execute_fork(t_node *pipe_nd, char **env_path, pid_t *pids)
{
	int	i;
	int	pipe_fd[2];
	int	*fd;

	i = 0;
	init_fd(&fd);
	while (pipe_nd)
	{
		connect_pipe1(pipe_nd, pipe_fd, fd);//right가 있으면 표준출력을 파이프 생성 후 입구에 연결
		set_signal_fork();//ctrl+c 신호 무시
		pids[i] = fork();//자식 프로세스 생성
		if (pids[i] == -1)
			print_errno(STD_ERROR, "fail execution_fork", NULL, 1);
		if (pids[i++] == 0)//자식이 들어가는 부분
		{
			if (pipe_nd->right)
				ft_close(pipe_fd[PIPE_OUT]);//새로 만든 파이프에는 입력만 할거라서
			exit(run_cmd(pipe_nd->left, fd, env_path));//자식프로세스에서 명령어 하나씩 실행
		}
		connect_pipe2(pipe_nd, pipe_fd, fd);//부모는 자식프로세스의 결과를 담은 파이프의 출구에 표준입력을 연결
		pipe_nd = pipe_nd->right;
	}
	free (fd);
	return (pids);
}

static void	connect_pipe1(t_node *pipe_nd, int *pipe_fd, int *fd)
{
	if (pipe_nd->right)//파이프가 존재하면
	{
		if (pipe(pipe_fd) == -1)
		{
			print_errno(STD_ERROR, "execution", NULL, -1);
			pipe_fd[STD_IN] = -1;
			pipe_fd[STD_OUT] = -1;
		}
		fd[STD_OUT] = pipe_fd[PIPE_IN];//표준출력을 파이프 입구에 연결
	}
	else
		fd[STD_OUT] = STD_OUT;//아니면 그냥 그대로
}

static void	connect_pipe2(t_node *pipe_nd, int *pipe_fd, int *fd)
{
	if (fd[STD_IN] > 2)
		ft_close(fd[STD_IN]);
	if (pipe_nd->right)
	{
		fd[STD_IN] = pipe_fd[PIPE_OUT];
		ft_close(fd[STD_OUT]);
	}
}
