#ifndef TREE_H
# define TREE_H

enum e_ttype//열거형
{
	T_NULL = 0,
	T_WORD = 1,
	T_REDIR = 2,
	T_PIPE = 3,
	T_CMD = 4,
	T_CMD_OPTION = 5,
	T_AND = 6,
	T_OR = 7
};

typedef struct s_node{
	enum e_ttype	type;
	char			*str1;
	char			**str2;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*parent;
}	t_node;

typedef struct s_tree
{
	t_node	*top;
	int		node_count;
}	t_tree;

#endif
