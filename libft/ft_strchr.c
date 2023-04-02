/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:27:15 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/14 16:31:17 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int i)
{
	char	find;
	int		idx;

	find = (unsigned char)i;
	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == find)
			return ((char *)str + idx);
		idx++;
	}
	if (str[idx] == find)
		return ((char *)str + idx);
	return (0);
}
