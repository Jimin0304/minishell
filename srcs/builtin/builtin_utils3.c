/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:02:12 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:02:14 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2, char *s3)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (new == NULL)
		malloc_failed(s3);
	return (new);
}

char	*ft_strdup2(char *s1, char *s2)
{
	char	*new;

	new = ft_strdup(s1);
	if (new == NULL)
		malloc_failed(s2);
	return (new);
}

char	*ft_substr2(char *s1, int start, int size, char *s2)
{
	char	*new;

	new = ft_substr(s1, start, size);//s1문자열의 start인덱스부터 size개수의 문자를 복사해서 반화
	if (new == NULL)
		malloc_failed(s2);
	return (new);
}

void	*ft_calloc2(size_t count, size_t size, char *s)
{
	void	*tmp;

	tmp = ft_calloc(count, size);
	if (tmp == NULL)
		malloc_failed(s);
	return (tmp);
}
