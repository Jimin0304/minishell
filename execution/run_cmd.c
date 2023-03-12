#include "minishell.h"
#include "execution.h"
#include "error.h"
#include "builtin.h"

static char	*get_cmd_path(char *cmd, char **env_path);

int	run_cmd(t_node *cmd_nd, int *fd, char **env_path)
{
	int	rtn;

	rtn = -1;
	setting_terminal();
	set_signal_origin();
	if (redirection(cmd_nd->left, fd) == -1)
		return (1);
	if (cmd_nd->right == NULL)
		return (0);
	rtn = run_builtin(cmd_nd->right, fd);
	if (rtn != -1)//빌트인 명령어중 하나가 실행된것...? -1이면 빌트인 명령어가 아님
		return (rtn);
	running_cmd(cmd_nd->right, env_path);//명령어 실행
	if (errno == 14)
		return (print_error(fd[STD_ERROR], cmd_nd->right->str1, \
												"command not found", 127));
	else if (errno == 13 || errno == 20)
		return (print_errno(fd[STD_ERROR], cmd_nd->right->str1, NULL, 126));
	else if (errno == 2)
		return (print_errno(fd[STD_ERROR], cmd_nd->right->str1, NULL, 127));
		print_errno(fd[STD_ERROR], cmd_nd->right->str1, NULL, 1);
	return (1);
}

void	running_cmd(t_node *simpcmd, char **env_path)
{
	char	*file_path;

	file_path = NULL;
	if (ft_strrchr(simpcmd->str1, '/') != NULL || env_path == NULL)
	{
		file_path = safe_ft_substr(simpcmd->str2[0], 0, \
					ft_strlen(simpcmd->str2[0]), "simp_cmd");
		if (file_path == NULL)
			return ;
	}
	else
		file_path = get_cmd_path(simpcmd->str1, env_path);
	execve(file_path, simpcmd->str2, g_envp_list);
}

static char	*get_cmd_path(char *cmd, char **env_path)
{
	char		*cmd_path;
	char		*tmp;
	int			i;
	struct stat	buf;

	i = 0;
	if (cmd == NULL || cmd[0] == '\0' || env_path == NULL)
		return (NULL);
	while (env_path[i])
	{
		tmp = safe_ft_strjoin(env_path[i], "/", "get_cmd_path");
		cmd_path = safe_ft_strjoin(tmp, cmd, "get_cmd_path");
		free(tmp);
		if (stat(cmd_path, &buf) == 0)//존재하는 파일(명령어)면 만족하는 조건
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
