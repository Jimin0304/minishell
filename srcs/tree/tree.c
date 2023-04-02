/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:10:57 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:10:59 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include	"error.h"

cmd_tree	*create_tree(void)
{
	cmd_tree	*new_tree;

	new_tree = (cmd_tree *)malloc(sizeof(cmd_tree));
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

int	tree_connect_node_left(cmd_tree *tree, t_node *cur_node, t_node *new_node)
{
	if (cur_node->left != NULL)
		return (-1);
	cur_node->left = new_node;
	new_node->up = cur_node;
	tree->node_count++;
	return (1);
}

int	tree_connect_node_right(cmd_tree *tree, t_node *cur_node, t_node *new_node)
{
	if (cur_node->right != NULL)
		return (-1);
	cur_node->right = new_node;
	new_node->up = cur_node;
	tree->node_count++;
	return (1);
}
