/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:59:03 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 11:29:05 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

cmd_tree	*start_tokenize(char *s)
{
	t_node	*list;
	cmd_tree	*tokens;

	list = NULL;
	s = get_env_tokenizer(s);//사용자 입력값에서 환경변수 키를 확인하고 벨류값으로 치환
	if (s == NULL)
		return (NULL);
	change_whitespace(s);// 공백에 자리에 -1 삽입
	s = change_oper(s); // |,<,>의 기호 앞뒤로 -1 삽입
	list = split_str(s);// 사용자 입력 문자열을 공백 기준으로 노드에 담은 연결리스트를 반환
	free (s);
	if (list == NULL)
		return (NULL);
	tokens = create_tree();
	tokens->top = list;
	return (tokens);
}

void	change_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i += skip_dquot(&s[i]);
		}
		else if (is_whitespace(s[i]))
			s[i] = -1;
		if (s[i] != '\0')
			i++;
	}
}

char	*change_oper(char *s)
{
	s = change_each_oper(s, '|');// | 기호 앞뒤로 -1 삽입
	s = change_redir(s, '<'); // 리다이렉션 기호도 마찬가지
	s = change_redir(s, '>');
	return (s);
}

char	*change_each_oper(char *s, char op)
{
	char	*str;
	t_index	*idx;
	int		k;

	idx = make_idx();
	str = malloc(sizeof(char) * (count_new_space(s, op) + 2));
	if (str == NULL)
		malloc_failed(NULL);
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"' || s[idx->i] == '\'')
		{
			k = skip_dquot(&s[idx->i]);
			while (k-- && s[idx->i] != '\0')
				str[idx->j++] = s[idx->i++];
		}
		perform_change_each_oper(str, s, idx, op);
	}
	str[idx->j] = '\0';
	free(s);
	free(idx);
	return (str);
}

char	*change_redir(char *s, char op)
{
	char	*str;
	t_index	*idx;
	int		k;

	idx = make_idx();
	str = malloc(sizeof(char) * (count_new_space(s, op) + 2));
	if (str == NULL)
		malloc_failed(NULL);
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"' || s[idx->i] == '\'')
		{
			k = skip_dquot(&s[idx->i]);
			while (k-- && s[idx->i] != '\0')
				str[idx->j++] = s[idx->i++];
		}
		perform_change_redir(str, s, idx, op);
	}
	str[idx->j] = '\0';
	free(s);
	free(idx);
	return (str);
}
