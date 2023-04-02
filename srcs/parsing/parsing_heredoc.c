/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:00:03 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:00:05 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h" 
#include "execution.h"
#include "signal2.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

static int	heredoc_child(char *key, char *file_path);
static char	*create_filepath(void);
static int	heredoc_child_write(char *file_path, char *str);

int	heredoc(char *key, t_node *node)
{
	char	*file_path;
	pid_t	pid;
	int		stat_loc;
	int		flag;

	file_path = create_filepath();//파일경로 생성
	if (file_path == NULL)
		return (print_errno(STD_ERROR, \
					"fail heredoc make_filepath", NULL, 2));
	pid = fork();
	if (pid == 0)//자식 프로세스 파트
		exit(heredoc_child(key, file_path));
	else if (pid == -1)
	{
		free (file_path);
		return (print_errno(STD_ERROR, "fail heredoc fork", NULL, 2));
	}
	set_signal_fork();//SIG_INT,SIG_QUIT 신호 무시
	waitpid(pid, &stat_loc, 0);//자식프로세스 기다리면서 종료상태 받음
	set_signal();//
	flag = check_exit_status(stat_loc);//자식 종료상태 체크
	free(node->str2[0]);
	node->str2[0] = file_path;
	return (flag);
}

static int	heredoc_child(char *key, char *file_path)
{
	char	*str;
	char	*new;
	char	*tmp;

	str = ft_calloc2(1, sizeof(char), "heredoc");
	str[0] = '\0';
	set_signal_heredoc();
	while (1)
	{
		new = readline("> ");
		if (new == NULL)
			break ;
		if (ft_strncmp(key, new, ft_strlen(key) + 1) != 0)
		{
			tmp = ft_strjoin2(str, new, "heredoc");
			free(str);
			free(new);
			str = ft_strjoin2(tmp, "\n", "heredoc");
			continue ;
		}
		free (new);
		break ;
	}
	return (heredoc_child_write(file_path, str));
}

static int	heredoc_child_write(char *file_path, char *str)
{
	int	fd;
	//printf("%s\n",file_path);
	fd = open(file_path, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
		return (print_errno(STD_ERROR, "fail heredoc_child", file_path, 1));
	ft_putstr_fd(str, fd);
	close (fd);
	return (0);
}

static char	*create_filepath(void)
{
	char		*file_path;
	char		*tmp;
	struct stat	buf;

	tmp = "random";
	file_path = ft_strjoin2(tmp, "a", "heredoc");
	while (file_path && file_path[ft_strlen(file_path) - 1] <= 'z')
	{
		if (stat(file_path, &buf) == -1)
			break ;
		file_path[ft_strlen(file_path) - 1]++;
	}
	if (errno != 2 || file_path[ft_strlen(file_path) - 1] > 'z')
	{
		free (file_path);
		file_path = NULL;
	}
	return (file_path);
}
