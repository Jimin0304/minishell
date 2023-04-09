/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:00:59 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/09 18:03:57 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "error.h"
#include "builtin.h"

static int	is_builtin(t_node *simp_cmd_nd);

int	run_builtin(t_node *simp_cmd, int *fd)
{
	int	flag;

	flag = 0;
	if (simp_cmd->str1 == NULL)
		return (-1);
	if (fd == NULL)
		return (-1);
	if (ft_strncmp(simp_cmd->str1, "echo", 5) == 0)
		flag = perform_echo(simp_cmd->str2, fd);
	else if (ft_strncmp(simp_cmd->str1, "cd", 3) == 0)
		flag = perform_cd(simp_cmd->str2, fd);
	else if (ft_strncmp(simp_cmd->str1, "pwd", 4) == 0)
		flag = perform_pwd(fd);
	else if (ft_strncmp(simp_cmd->str1, "export", 7) == 0)
		flag = perform_export(simp_cmd->str2, fd);
	else if (ft_strncmp(simp_cmd->str1, "unset", 6) == 0)
		flag = perform_unset(simp_cmd->str2, fd);
	else if (ft_strncmp(simp_cmd->str1, "env", 4) == 0)
		flag = perform_env(fd);
	else if (ft_strncmp(simp_cmd->str1, "exit", 5) == 0)
		flag = perform_exit(simp_cmd->str2, fd);
	else
		return (-1);
	return (flag);
}

int	noconnect_pipe_builtin(t_tree *tree)
{
	int		exit_flag;
	t_node	*cmd_nd;
	t_node	*sim_cmd_nd;
	int		*fd;

	exit_flag = 1;
	cmd_nd = tree->top->left;
	sim_cmd_nd = cmd_nd->right;
	if (tree->top->right || sim_cmd_nd == NULL || sim_cmd_nd->str1 == NULL)
		return (-1);
	if (is_builtin(sim_cmd_nd) == -1)//빌트인에 해당하는 명령어인 경우 해당 함수는 1을 반환
		return (-1);
	if (init_fd(&fd) == -1)
		return (exit_flag);
	if (set_redirection(cmd_nd->left, fd))//리다이렉션이 존재한다면 표준입력과 출력은 리다이렉션(데이터의 이동방향설정)되어있음
		exit_flag = run_builtin(sim_cmd_nd, fd);
	if (fd[STD_IN] > 2)
		close2(fd[STD_IN]);
	if (fd[STD_OUT] > 2)
		close2(fd[STD_OUT]);
	if (fd[STD_ERROR] > 2)
		close2(fd[STD_ERROR]);
	free(fd);
	return (exit_flag);
}

static int	is_builtin(t_node *simp_cmd_nd)
{
	if (simp_cmd_nd == NULL || simp_cmd_nd->str1 == NULL)
		return (-1);
	if (ft_strncmp(simp_cmd_nd->str1, "echo", 5) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "cd", 3) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "pwd", 3) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "export", 7) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "unset", 6) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "env", 4) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "exit", 5) == 0)
		ft_putstr_fd("exit\n", STD_OUT);
	else
		return (-1);
	return (1);
}
