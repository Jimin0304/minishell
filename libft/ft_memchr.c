/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:15:38 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/14 16:30:47 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	while (n)
	{
		if (*(unsigned char *)src == (unsigned char)c)
			return ((void *)src);
		src++;
		n--;
	}
	return (0);
}
