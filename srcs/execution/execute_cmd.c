/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:01:04 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/09 18:05:00 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "error.h"
#include "signal2.h"
#include "builtin.h"

static char	*get_cmd_path(char *cmd, char **env_path);

int	execute_cmd(t_node *cmd_nd, int *fd, char **env_path)
{
	int	flag;

	flag = -1;
	set_terminal_print_on();
	set_signal_origin();
	if (redirection(cmd_nd->left, fd) == -1)//리다이렉션 처리 및 표준입출력 파이프와 연결
		return (1);
	if (cmd_nd->right == NULL)
		return (0);
	flag = run_builtin(cmd_nd->right, fd);//-1이 반환되면 빌트인 명령어는 실행되지 않음
	if (flag != -1)//빌트인 명령이 실행된 경우
		return (flag);
	execute_scmd(cmd_nd->right, env_path);
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

void	execute_scmd(t_node *scmd, char **env_path)
{
	char	*file_path;

	file_path = NULL;
	if (ft_strrchr(scmd->str1, '/') != NULL || env_path == NULL)//경로를 지정해서 들어온 명령이거나 환경변수가 없을때
	{
		file_path = ft_substr2(scmd->str2[0], 0, \
					ft_strlen(scmd->str2[0]), "simp_cmd");
		if (file_path == NULL)
			return ;
	}
	else
		file_path = get_cmd_path(scmd->str1, env_path);//경로지정이 되어있지 않고 환경변수가 존재할때
	execve(file_path, scmd->str2, g_envp_list);//2번째 인자에는 명령어와 명령어의 옵션이 담겨있는 문자열
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
		tmp = ft_strjoin2(env_path[i], "/", "get_cmd_path");
		cmd_path = ft_strjoin2(tmp, cmd, "get_cmd_path");
		free(tmp);
		if (stat(cmd_path, &buf) == 0)//해당 경로에 명령어가 존재하면 0을 반환하는 함수
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
