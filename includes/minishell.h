/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:10:22 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 11:29:05 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error.h"
# include "builtin.h"

char	**envp_list;//환경변수
int		final_exit_status;//종료상태

enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1,
	STD_ERROR = 2
};

enum e_ttype
{
	T_NULL = 0,
	T_WORD = 1,
	T_REDIR = 2,
	T_PIPE = 3,
	T_CMD = 4,
	T_SCMD = 5,
};

typedef struct s_node{
	enum e_ttype	type;
	char			*str1;
	char			**str2;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*up;
}	t_node;

typedef struct s_tree
{
	t_node	*top;
	int		node_count;
}	cmd_tree;

//파싱
void	process_and_execution(char *str);
char	**get_env(char **envp);
void	malloc_failed(char *str);

t_node	*parse_get_tokens_top(cmd_tree *tree);
int		parsing_add_redirect(cmd_tree *tree, cmd_tree *tokens, \
												t_node *cur_cmd_nd);
int		add_pipe_cmd(cmd_tree *tree, cmd_tree *tokens, \
												t_node *cur_pipe_nd);
int		parsing_add_scmd(cmd_tree *tree, cmd_tree *tokens, t_node *cur_cmd_nd);
int		cnt_wordnd(t_node *node);

int		heredoc(char *key, t_node *node);
int		parsing(cmd_tree **tokens);
int		start_parsing(cmd_tree *tree, cmd_tree *tokens, t_node **cur_pipe);
int		parsing_redirect(cmd_tree *tree, cmd_tree *tokens, \
								t_node *cur_cmd_nd, t_node *cur_tokens_node);
int		parsing_word(cmd_tree *tree, cmd_tree *tokens, \
								t_node *cur_cmd_nd, t_node *cur_tokens_node);
int		parsing_pipe(cmd_tree *tree, cmd_tree *tokens, t_node **cur_pipe_nd);
void	parsing_error(char *str);

//토큰
cmd_tree	*start_tokenize(char *s);
void	change_whitespace(char *s);
char	*change_each_oper(char *s, char op);
char	*change_redir(char *s, char op);
char	*change_oper(char *s);
int		is_whitespace(char c);
int		skip_dquot(char *s);
int		count_new_space(char *s, char c);
t_node	*split_str(char *str);
t_node	*make_new(char *str, int size);
void	add_next(t_node *new, t_node *start);
void	perform_change_redir(char *str, char *s, t_index *idx, char op);
void	perform_change_each_oper(char *str, char *s, t_index *idx, char op);
char	*get_env_to_str(char *env_name);
char	*get_env_tokenizer(char *s);
char	*remove_dequot(char **s);
void	perform_remove_dequot(char *new_str, char *s, char c, t_index *idx);
char	*get_env_name(char *s);
int		get_env_name_size(char *s);
char	*get_merged_env_str(char *s, char *env);
char	*ft_strjoin_check_null(char *s1, char *s2);
int		check_double_flag(char *s, int double_flag);
char	*fix_dol(char *str);
void	change_exit_status(int num);
char	*free_ret(char *env_name, char *str);
char	*get_merged_str(char *str, t_index *i);
int		check_input_whitespace(char *str);

//트리
cmd_tree	*create_tree(void);
t_node	*tree_create_node(enum e_ttype type, char *str);
int		tree_connect_node_left(cmd_tree *tree, t_node *cur_node, \
												t_node *new_node);
int		tree_connect_node_right(cmd_tree *tree, t_node *cur_node, \
												t_node *new_node);

void	tree_clear_node(t_node *node);
void	tree_delete_nodes(t_node *node);
void	tree_delete(cmd_tree *tree);

#endif
