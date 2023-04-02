/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:10:58 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/14 16:30:47 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			idx;
	unsigned char	*b1;
	unsigned char	*b2;

	idx = 0;
	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	while (n)
	{
		if (b1[idx] != b2[idx] || b1[idx] == 0 || b2[idx] == 0)
			return (b1[idx] - b2[idx]);
		idx++;
		n--;
	}
	return (0);
}
