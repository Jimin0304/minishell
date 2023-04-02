/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:59:09 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 04:57:24 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"

char	*free_ret(char *env_name, char *str)
{
	free(env_name);
	if (str == NULL)
		return (NULL);
	return (ft_strdup2(str, "get_env"));
}

int	check_double_flag(char *s, int double_flag)
{
	if (double_flag == 1)//double_flag가 1이면 인용구의 짝이 맞는거임
		double_flag = 0;//그런 상태에서 이 함수를 호출했으므로 double_flag를 0으로 만듬
	else if (skip_dquot(s) != 0 && double_flag == 0)//skip_dquot는 "뒤에 더이상 "이 없으면 0반환 있으면 인덱스값 반환
		double_flag = 1;
	return (double_flag);
}
