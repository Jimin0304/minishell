/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:10:51 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:10:52 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include	"libft.h"
#include	<sys/stat.h>

void	tree_clear_node(t_node *node)
{
	int			i;
	struct stat	buf;

	i = 0;
	if (node == NULL)
		return ;
	if (node->type == T_REDIR && node->str1 \
		&& ft_strncmp(node->str1, "<<", 3) == 0)
	{
		if (node->str2 && node->str2[0] && stat(node->str2[0], &buf) == 0)
			unlink(node->str2[0]);
	}
	if (node->str1 != NULL)
		free(node->str1);
	if (node->str2 != NULL)
	{
		while (node->str2 && node->str2[i])
			free(node->str2[i++]);
		free(node->str2);
	}
}

void	tree_delete_nodes(t_node *node)
{
	if (node == NULL)
		return ;
	tree_delete_nodes(node->left);
	tree_delete_nodes(node->right);
	tree_clear_node(node);
	free (node);
}

void	tree_delete(cmd_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->top)
		tree_delete_nodes(tree->top);
	free(tree);
}
