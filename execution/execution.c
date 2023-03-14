#include "minishell.h"
#include "execution.h"
#include "error.h"


static char		**execute_get_path(char **envp_list);
static pid_t	*execute_init_pids(t_tree *tree);
static void		execute_free_env_path(char **env_path);

int	execution(t_tree *tree)
{
	pid_t	*pids;
	int		exit_status;
	char	**env_path;

	if (tree == NULL)
		return (258);
	env_path = execute_get_path(g_envp_list);//환경변수 받아놓기
	exit_status = -1;
	if (tree->top->right == NULL)//파이프 노드가 하나밖에 없을때 == 입력에 파이프가 존재하지 않는 경우
		exit_status = no_pipe_builtin(tree);//0 반환하면 명령어 정상실행 된것
	if (exit_status == -1)//파이프가 하나이상 존재하면 여기로 들어감
	{
		pids = execute_init_pids(tree);//파이프노드 개수만큼 pid 형 배열생성
		if (pids == NULL)
		{
			execute_free_env_path(env_path);
			return (1);
		}
		execute_fork(tree->top, env_path, pids);
		exit_status = execute_wait_child(pids);
		set_signal();
		free(pids);
	}
	execute_free_env_path(env_path);
	return (exit_status);
}

static char	**execute_get_path(char **envp_list)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	path = NULL;
	while (envp_list[i])
	{
		if (ft_strncmp(envp_list[i], "PATH=", 5) == 0)
		{
			tmp = safe_ft_substr(envp_list[i], 5, \
								ft_strlen(envp_list[i]) - 5, "executor");
			if (tmp)
			{
				path = ft_split(tmp, ':');
				free (tmp);
				if (path == NULL)
					exit (print_errno(STD_ERROR, "fail get_path", NULL, 1));
			}
			return (path);
		}
		i++;
	}
	return (NULL);
}

static pid_t	*execute_init_pids(t_tree *tree)
{
	t_node	*pipe_nd;
	int		cnt;
	pid_t	*pids;

	pipe_nd = tree->top;
	cnt = 0;
	while (pipe_nd)
	{
		pipe_nd = pipe_nd->right;
		cnt++;
	}
	pids = safe_ft_calloc(cnt + 1, sizeof(pid_t), "fail init pids");//파이프노드개수 +1 만큼 pids를 만듬
	return (pids);
}

static void	execute_free_env_path(char **env_path)
{
	int	i;

	i = 0;
	if (env_path == NULL)
		return ;
	while (env_path[i])
		free(env_path[i++]);
	free(env_path);
}
