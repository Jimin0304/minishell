/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:58:37 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/09 18:05:00 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

#include "libft.h"
#include "error.h"

char	*remove_dequot(char **str)//인용어구 기호를 삭제하고 문자열만 반환해주는 함수,인용어구 짝이 맞지 않으면 삭제안함
{
	char	*s;
	char	*new_str;
	t_index	*idx;

	s = *str;
	idx = make_idx();
	new_str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (new_str == NULL)
		malloc_failed("remove_dequot");
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"')
			perform_remove_dequot(new_str, s, '\"', idx);
		else if (s[idx->i] == '\'')
			perform_remove_dequot(new_str, s, '\'', idx);
		else
			new_str[idx->j++] = s[idx->i++];
	}
	new_str[idx->j] = '\0';
	free (s);
	free (idx);
	*str = new_str;
	return (new_str);
}

void	perform_remove_dequot(char *new_str, char *s, char c, t_index *idx)
{
	if (check_dequot(&s[idx->i]))
	{
		idx->i++;
		while (s[idx->i] != c)
			new_str[idx->j++] = s[idx->i++];
		idx->i++;
	}
	else
		new_str[idx->j++] = s[idx->i++];
}

char	*ft_strjoin_check_null(char *s1, char *s2)
{
	char	*result;

	if (s1 != NULL && s2 != NULL)
	{
		result = ft_strjoin2(s1, s2, "make_str");
		free(s1);
		free(s2);
		return (result);
	}
	if (s1 == NULL && s2 != NULL)
	{
		result = ft_strdup2(s2, "make_str");
		free(s2);
		return (result);
	}
	if (s1 != NULL && s2 == NULL)
	{
		result = ft_strdup2(s1, "make_str");
		free(s1);
		return (result);
	}
	return (NULL);
}

void	change_exit_flag(int num)
{
	free(g_envp_list[0]);
	g_envp_list[0] = ft_itoa(num);
	if (g_envp_list[0] == NULL)
		malloc_failed("change_exit_flag");
}

void	malloc_failed(char *str)
{
	print_errno(STD_ERROR, str, NULL, -1);
	exit (1);
}
