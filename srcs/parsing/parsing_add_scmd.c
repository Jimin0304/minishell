/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_scmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:00:17 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/05 17:12:41 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

static	void	parsing_add_scmd_new(t_tree *tokens, t_node *cur_cmd_nd);
static	void	parsing_add_scmd_extend(t_tree *tokens, t_node *token);

int	parsing_add_scmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*token;
	t_node	*tmp;
	int		cnt;

	if (tree == NULL || tokens == NULL \
		|| tree->top == NULL || cur_cmd_nd == NULL)
		return (-1);
	if (cur_cmd_nd->right == NULL)
		parsing_add_scmd_new(tokens, cur_cmd_nd);//cmd노드 오른쪽 아래에 탑토큰으로 scmd 생성
	else
		parsing_add_scmd_extend(tokens, cur_cmd_nd->right);//scmd 노드의 [문자열 배열]의 크기를 연속적인 T_word 노드의 개수만큼 확장한다.
	token = cur_cmd_nd->right;
	cnt = 1;
	while (token->str2[cnt])
		cnt++;
	while (tokens->top->type == T_WORD)// 이 반복문에서 scmd노드의 [문자열 배열]에다가 토큰리스트에서 T_word인 노드들의 문자열들을 순차적으로 담는다
	{
		tmp = parse_get_tokens_top(tokens);
		token->str2[cnt++] = tmp->str1;
		free(tmp);
	}
	token->str2[cnt] = NULL;
	return (1);
}

static void	parsing_add_scmd_new(t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*token;

	token = parse_get_tokens_top(tokens);
	token->type = T_SCMD;
	cur_cmd_nd->right = token;
	token->str2 = ft_calloc2(cnt_wordnd(tokens->top) + 2, \
									sizeof(char *), "fail add_simcmd");
	token->str2[0] = ft_strdup2(token->str1, "fail add_simcmd");
	token->str2[1] = NULL;
}

static void	parsing_add_scmd_extend(t_tree *tokens, t_node *token)
{
	int		i;
	char	**str2;

	i = 0;
	while (token->str2[i])
		i++;
	str2 = ft_calloc2(cnt_wordnd(tokens->top) + i + 1, \
								sizeof(char *), "fail add_simcmd");//cnt_wordnd함수를 호출해서 연속적인 T_word 노드의 개수를 파악
	i = 0;
	while (token->str2[i])// 이 반복문에서 기존에 scmd 노드에 담겨있는 문자열이 있으면 옮긴다.
	{
		str2[i] = token->str2[i];
		i++;
	}
	str2[i] = NULL;
	free (token->str2);
	token->str2 = str2;
}
