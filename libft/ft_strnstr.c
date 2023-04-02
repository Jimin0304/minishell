/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:25:18 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/14 16:30:47 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	b_len;
	size_t	l_len;
	size_t	size;

	if (*little == '\0')
		return ((char *)big);
	b_len = ft_strlen(big);
	l_len = ft_strlen(little);
	if (b_len < l_len || n < l_len)
		return (0);
	if (b_len > n)
		size = n;
	else
		size = b_len;
	while (size >= l_len)
	{
		if (ft_memcmp(big, little, l_len) == 0)
			return ((char *)big);
		big++;
		size--;
	}
	return (0);
}
