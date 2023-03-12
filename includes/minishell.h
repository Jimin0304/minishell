# ifndef MINISHELL_H
# define MINISHELL_H

# include "tree.h"

char	**g_envp_list;

enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1,
	STD_ERROR = 2
};

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
}	t_index;

void	run_minishell(char *str);
char	**get_env(char **envp);
void	malloc_failed(char *str);

#endif
