/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:59:03 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/05 17:12:41 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

t_tree	*start_tokenize(char *s)
{
	t_node		*list;
	t_tree	*tokens;
	int			i;

	list = NULL;
	s = get_env_tokenizer(s);//사용자 입력값에서 환경변수 키를 확인하고 벨류값으로 치환
	i = change_whitespace(s);// 공백에 자리에 -1 삽입
	if (i == -1 || i == -2)
	{
		if (i == -2)
			printf("minishell: syntax error near unexpected token '\''\n");
		else
			printf("minishell: syntax error near unexpected token '\"'\n");
		return (NULL);
	}
	s = change_oper(s); // |,<,>의 기호 앞뒤로 -1 삽입
	list = split_str(s);// 사용자 입력 문자열을 공백 기준으로 노드에 담은 연결리스트를 반환
	free (s);
	if (list == NULL)
		return (NULL);
	tokens = create_tree();
	tokens->top = list;
	return (tokens);
}

int	change_whitespace(char *s)
{
	int		i;
	int		tmp;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			tmp = check_dquot_error(&s[i]);
			if (tmp == -1 || tmp == -2)
				return (tmp);
			i += tmp;
		}
		else if (is_whitespace(s[i]))
			s[i] = -1;
		if (s[i] != '\0')
			i++;
	}
	return (0);
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
