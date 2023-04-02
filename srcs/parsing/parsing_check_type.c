/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:00:11 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:19:30 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_check_type(cmd_tree *tree, cmd_tree *tokens, t_node *cur_cmd)
{
	int		rtn;
	t_node	*next;

	rtn = 258;
	next = tokens->top->left;
	if (tokens->top->type == T_WORD && remove_dequot(&tokens->top->str1))
		rtn = parsing_word(tree, tokens, cur_cmd, next);
	else if (tokens->top->type == T_REDIR)
		rtn = parsing_redirect(tree, tokens, cur_cmd, next);
	else if (tokens->top->type == T_PIPE)
		rtn = parsing_pipe(tree, tokens, &cur_cmd->up);//3번째 인자는 파이프 노드의 주소임
	else if (tokens->top->type == T_NULL)
		rtn = 0;
	else
		parsing_error(tokens->top->str1);
	return (rtn);
}

int	parsing_redirect(cmd_tree *tree, cmd_tree *tokens,
							t_node *cur_cmd, t_node *cur_token)
{
	int		rtn;

	rtn = 258;
	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_token == NULL)
		return (rtn);
	if (cur_token->type == T_WORD && remove_dequot(&cur_token->str1))//리다이렉션 기호 다음에 문자열이 있을때
	{
		rtn = parsing_add_redirect(tree, tokens, cur_cmd);
		if (rtn == 0)//리다이렉션 노드랑 파일노드에 대응되는 문자열들을 성공적으로 처리했을때
			rtn = parsing_check_type(tree, tokens, cur_cmd);
	}
	else
		parsing_error(cur_token->str1);
	return (rtn);
}

int	parsing_word(cmd_tree *tree, cmd_tree *tokens, \
						t_node *cur_cmd, t_node *cur_tokens)
{
	int		rtn;

	rtn = 258;
	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_tokens == NULL)
		return (rtn);
	if (cur_tokens->type == T_WORD && remove_dequot(&cur_tokens->str1))
		rtn = parsing_word(tree, tokens, cur_cmd, cur_tokens->left);
	else
	{
		if (parsing_add_scmd(tree, tokens, cur_cmd) == -1)// 여기서 cmd노드 오른쪽 아래에 scmd 노드가 만들어서 토큰연결리스트의 T_word의 노드의 문자열들을 담아둔다
			return (rtn);
		rtn = parsing_check_type(tree, tokens, cur_cmd);
	}
	return (rtn);
}

int	parsing_pipe(cmd_tree *tree, cmd_tree *tokens, t_node **cur_pipe)
{
	int		rtn;

	rtn = add_pipe_cmd(tree, tokens, *cur_pipe);
	if (tokens->top->type == T_WORD && remove_dequot(&tokens->top->str1))//사용자 입력에서 파이프 다음에 문자열 노드가 있을때
		rtn = -2;
	else if (tokens->top->type == T_REDIR)//사용자 입력에서 파이프 다음에 리다이렉션 기호가 있을때
		rtn = -2;
	else
	{
		parsing_error(tokens->top->str1);
		rtn = 258;
	}
	return (rtn);
}
