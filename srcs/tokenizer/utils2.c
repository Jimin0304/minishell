/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:58:48 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 11:29:05 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"

t_node	*split_str(char *str)
{
	t_node		*start;
	int			i;
	int			save;

	i = 0;
	start = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == -1)// 공백은 건더뛰다가
			i++;
		else
		{
			save = i;//공백이 아닌문자의 인덱스값 백업해놓고
			while (str[i] != -1 && str[i] != '\0')
				i++;
			if (start == NULL)
				start = make_new(&str[save], i - save);// i - save == 공백을 기준으로 한 문자열의 길이, 해당 문자열과 문자열의 종류의 정보를 가진 노드를 반환
			else
				add_next(make_new(&str[save], i - save), start);// make_new로 만들어진 노드를 계속해서 왼쪽 끝에 붙인다.
		}
	}
	if (start != NULL)
		add_next(tree_create_node(T_NULL, NULL), start);
	return (start);
}

t_node	*make_new(char *str, int size)
{
	t_node	*new;
	char	*new_str;
	int		type;

	if (size == 0)
		return (NULL);
	new_str = ft_substr2(str, 0, size, "make_new");
	if (new_str[0] == '|')
		type = T_PIPE;
	else if (new_str[0] == '<')
	{
		type = T_REDIR;
	}
	else if (new_str[0] == '>')
		type = T_REDIR;
	else
		type = T_WORD;
	new = tree_create_node(type, new_str);
	return (new);
}

void	add_next(t_node *new, t_node *start)
{
	t_node	*curr;

	curr = start;
	while (curr->left != NULL)
		curr = curr->left;
	curr->left = new;
}

void	perform_change_redir(char *str, char *s, t_index *idx, char op)
{
	if (s[idx->i] == op && s[idx->i + 1] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else if (s[idx->i] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else
		str[idx->j++] = s[idx->i++];
}

void	perform_change_each_oper(char *str, char *s, t_index *idx, char op)
{
	if (s[idx->i] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else
		str[idx->j++] = s[idx->i++];
}
