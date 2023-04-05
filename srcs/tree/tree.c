/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:10:57 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/05 17:12:41 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include	"error.h"

t_tree	*create_tree(void)
{
	t_tree	*new_tree;

	new_tree = (t_tree *)malloc(sizeof(t_tree));
	if (new_tree == NULL)
		exit(print_errno(2, "fail create tree", NULL, 1));
	new_tree->top = NULL;
	new_tree->node_count = 0;
	return (new_tree);
}

t_node	*tree_create_node(enum e_ttype type, char *str)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(print_errno(2, "fail create tree_node", NULL, 1));
	new_node->type = type;
	new_node->str1 = str;
	new_node->str2 = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->up = NULL;
	return (new_node);
}

int	tree_connect_node_left(t_tree *tree, t_node *cur_node, t_node *new_node)
{
	if (cur_node->left != NULL)
		return (-1);
	cur_node->left = new_node;
	new_node->up = cur_node;
	tree->node_count++;
	return (1);
}

int	tree_connect_node_right(t_tree *tree, t_node *cur_node, t_node *new_node)
{
	if (cur_node->right != NULL)
		return (-1);
	cur_node->right = new_node;
	new_node->up = cur_node;
	tree->node_count++;
	return (1);
}
