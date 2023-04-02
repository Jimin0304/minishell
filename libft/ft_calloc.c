/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:09:55 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/14 16:30:47 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t n)
{
	void	*mem;

	mem = malloc(nmemb * n);
	if (!(mem))
		return (NULL);
	ft_bzero(mem, (nmemb * n));
	return (mem);
}
