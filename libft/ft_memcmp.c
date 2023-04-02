/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:20:59 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/14 16:30:47 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t n)
{
	size_t			idx;
	unsigned char	*s1;
	unsigned char	*s2;

	idx = 0;
	s1 = (unsigned char *)b1;
	s2 = (unsigned char *)b2;
	while (n)
	{
		if (s1[idx] != s2[idx])
			return (s1[idx] - s2[idx]);
		idx++;
		n--;
	}
	return (0);
}
