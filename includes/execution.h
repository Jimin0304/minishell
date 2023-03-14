#ifndef EXECUTION_H
# define EXECUTION_H

# include "tree.h"
# include <sys/wait.h>


int		execution(t_tree *tree);
pid_t	*execute_fork(t_node *pipe_nd, char **envp_list, pid_t *pids);
int		execute_wait_child(int *pids);

int		run_cmd(t_node *cmd_nd, int fd[2], char **envp_list);
void	running_cmd(t_node *simpcmd, char **envp_list);

int		redirection(t_node *redirct_nd, int *fd);
int		*set_redirection(t_node *redirct_nd, int *fd);
int		set_redirection_type(t_node *redirct_nd, int *fd);

int		run_builtin(t_node *simp_cmd, int *fd);
int		no_pipe_builtin(t_tree *tree);

int		exit_status(int statloc);
int		init_fd(int **fd);
void	ft_close(int fd);

#endif
