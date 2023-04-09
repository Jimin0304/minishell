/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:10:12 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/09 18:05:00 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/wait.h>

int		execution(t_tree *tree);
pid_t	*execution_fork(t_node *pipe_nd, char **g_envp_list, pid_t *pids);
int		execution_wait_child(int *pids);

int		execute_cmd(t_node *cmd_nd, int fd[2], char **g_envp_list);
void	execute_scmd(t_node *simpcmd, char **g_envp_list);

int		redirection(t_node *redirct_nd, int *fd);
int		*set_redirection(t_node *redirct_nd, int *fd);
int		set_redirection_type(t_node *redirct_nd, int *fd);

int		run_builtin(t_node *simp_cmd, int *fd);
int		noconnect_pipe_builtin(t_tree *tree);

int		check_exit_status(int statloc);
int		init_fd(int **fd);
void	close2(int fd);

#endif
