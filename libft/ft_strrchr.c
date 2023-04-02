/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:31:51 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/14 16:31:17 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int i)
{
	char	*last;
	char	find;
	size_t	idx;

	last = (char *)str;
	find = (char)i;
	idx = 0;
	idx = ft_strlen(str);
	while (idx > 0)
	{
		if (last[idx] == find)
			return (last + idx);
		idx--;
	}
	if (last[idx] == find)
		return (last);
	return (0);
}
