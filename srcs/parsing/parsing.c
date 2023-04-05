/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:59:55 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/05 17:12:41 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parsing(t_tree **tokens)//* == ->
{
	t_tree	*tree;
	int		parsing_flag;
	t_node	*cur_pipe;

	tree = create_tree();
	add_pipe_cmd(tree, NULL, NULL);//여기에서 tree의 탑은 이 함수에서 만든 파이프 노드를 가르키게 된다.
	cur_pipe = tree->top;
	while (1)
	{
		parsing_flag = start_parsing(tree, *tokens, &cur_pipe);
		if (parsing_flag == -2)//1개 이상의 파이프가 존재할때 파이프 이전의 문자열들을 정상적으로 파싱하고 파이프 기호 다음에 문자열이나 리다이렉션 기호가 있을때 -2를 반환
		{
			cur_pipe = cur_pipe->right;
			continue ;
		}
		else if (parsing_flag != 0)//파싱과정에서 오류가 발생시,0이 rtn이 0이라는 것은 파싱이 정상적으로 이루어진 것
		{
			tree_delete(tree);
			tree = NULL;
		}
		break ;
	}
	tree_delete(*tokens);
	*tokens = tree;
	return (parsing_flag);
}

int	start_parsing(t_tree *tree, t_tree *tokens, t_node **cur_pipe)//1번 인자는: 비어있는 트리, 2번: 만들어 놓은 트리, 3번: 탑 노드
{
	int		rtn;
	t_node	*cur_cmd;
	t_node	*next_tokens_node;
	t_node	*curr_tokens_node;

	cur_cmd = (*cur_pipe)->left;
	curr_tokens_node = tokens->top;
	next_tokens_node = tokens->top->left;
	if (curr_tokens_node->type == T_WORD && remove_dequot(&curr_tokens_node->str1))
		rtn = parsing_word(tree, tokens, cur_cmd, next_tokens_node);
	else if (curr_tokens_node->type == T_REDIR)
		rtn = parsing_redirect(tree, tokens, cur_cmd, next_tokens_node);
	else if (curr_tokens_node->type == T_NULL)
		rtn = 0 ;
	else
	{
		parsing_error(curr_tokens_node->str1);
		rtn = 258;
	}
	return (rtn);
}

void	parsing_error(char *str)
{
	if (str == NULL)
		print_error(STD_ERROR, \
		"syntax error near unexpected token 'newline'", NULL, 1);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '" \
		, STD_ERROR);
		ft_putstr_fd(str, STD_ERROR);
		ft_putstr_fd("'\n", STD_ERROR);
	}
}
