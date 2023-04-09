/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:00:38 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/09 18:05:00 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal2.h"
#include "execution.h"
#include "error.h"
#include "builtin.h"

static char		**execution_get_path(char **g_envp_list);
static pid_t	*execution_init_pids(t_tree *tree);
static void		execution_free_env_path(char **env_path);

int	execution(t_tree *tree)
{
	pid_t	*pids;
	int		exit_flag;
	char	**env_path;

	if (tree == NULL)
		return (258);
	env_path = execution_get_path(g_envp_list);
	exit_flag = -1;
	if (tree->top->right == NULL)//파이프가 1개도 없는 경우
		exit_flag = noconnect_pipe_builtin(tree);
	if (exit_flag == -1)
	{
		pids = execution_init_pids(tree);
		if (pids == NULL)
		{
			execution_free_env_path(env_path);
			return (1);
		}
		execution_fork(tree->top, env_path, pids);
		exit_flag = execution_wait_child(pids);
		set_signal();
		free(pids);
	}
	execution_free_env_path(env_path);
	return (exit_flag);
}

static char	**execution_get_path(char **g_envp_list)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	path = NULL;
	while (g_envp_list[i])
	{
		if (ft_strncmp(g_envp_list[i], "PATH=", 5) == 0)
		{
			tmp = ft_substr2(g_envp_list[i], 5, \
								ft_strlen(g_envp_list[i]) - 5, "execution");
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

static pid_t	*execution_init_pids(t_tree *tree)
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
	pids = ft_calloc2(cnt + 1, sizeof(pid_t), "fail init pids");
	return (pids);
}

static void	execution_free_env_path(char **env_path)
{
	int	i;

	i = 0;
	if (env_path == NULL)
		return ;
	while (env_path[i])
		free(env_path[i++]);
	free(env_path);
}
