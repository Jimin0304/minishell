/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:59:49 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/05 17:12:41 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

t_node	*parse_get_tokens_top(t_tree *tree)//탑노드를 하나 분리 후 가져오고 완쪽에 있는 노드를 탑에 위치시킨다.
{
	t_node	*tmp;

	if (tree == NULL || tree->top == NULL)
		return (NULL);
	tmp = tree->top;
	tree->top = tree->top->left;
	if (tree->top)
		tree->top->up = NULL;
	if (tmp->left)
		tmp->left = NULL;
	tree->node_count--;
	return (tmp);
}

int	parsing_add_redirect(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*redirection_node;
	t_node	*file_node;
	int		rtn;

	if (tree == NULL || tokens == NULL || cur_cmd_nd == NULL)
		return (-1);
	redirection_node = parse_get_tokens_top(tokens);//토큰 리스트에서 리다이렉션 노드 긁어오고
	file_node = parse_get_tokens_top(tokens);// 토큰 리스트에서 리다이렉션 노드 다음의(문자열노드)노드 긁어오고
	redirection_node->str2 = ft_calloc2(2, sizeof(char *), "fail add_redirect");//2개의 문자열의 공간을 0이라는 값으로 초기화하해서 반환
	redirection_node->str2[0] = file_node->str1;//리다이렉션 노드의 [문자열 리스트]에 파일명을 담아둔다
	redirection_node->str2[1] = NULL;
	if (cur_cmd_nd->left != NULL)//새로운 redirection 노드는 제일 왼쪽에 아래에 형성
	{
		cur_cmd_nd = cur_cmd_nd->left;
		while (cur_cmd_nd->left)
			cur_cmd_nd = cur_cmd_nd->left;
	}
	cur_cmd_nd->left = redirection_node;
	redirection_node->up = cur_cmd_nd;
	tree->node_count++;
	free(file_node);
	rtn = 0;
	if (ft_strncmp(redirection_node->str1, "<<", 3) == 0)//redir 노드에 해당기호가 존재하면 heredoc 호출
		rtn = heredoc(*redirection_node->str2, redirection_node);
	return (rtn);
}

int	add_pipe_cmd(t_tree *tree, t_tree *tokens, t_node *cur_pipe_nd)//사용1 : 파이프 노드가 없을때 호출 , 사용2 :
{
	t_node	*new_pipe;

	if (tree == NULL)
		return (-1);
	if (tokens == NULL)
		new_pipe = tree_create_node(T_PIPE, NULL);
	else
		new_pipe = parse_get_tokens_top(tokens);//여기서 파이프 기호가 top에 있기떄문에 파이프 노드를 반환
	if (new_pipe == NULL)
		exit(print_errno(STD_ERROR, "fail add_pipe_cmd", NULL, 1));
	new_pipe->left = tree_create_node(T_CMD, NULL);
	new_pipe->left->up = new_pipe;
	if (cur_pipe_nd == NULL && tree->top == NULL)
		tree->top = new_pipe;
	else
		cur_pipe_nd->right = new_pipe;//새로운 파이프 노드는 기존의 파이프 노드 오른쪽 아래에 생성
	return (1);
}

int	cnt_wordnd(t_node *node)
{
	int	cnt;

	cnt = 0;
	while (node->type == T_WORD)
	{
		node = node->left;
		cnt++;
	}
	return (cnt);
}
