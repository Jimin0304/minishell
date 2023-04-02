/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:28:03 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/13 19:24:06 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long		nbr;
	long		sign;
	size_t		idx;

	nbr = 0;
	sign = 1;
	idx = 0;
	while (str[idx] != '\0' && ft_isspace(str[idx]) == 1)
		idx++;
	if (str[idx] == '-')
		sign = -1;
	if (str[idx] == '-' || str[idx] == '+')
		idx++;
	while (str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9')
	{
		nbr = (nbr * 10) + (str[idx] - '0');
		if (nbr > 2147483647 && sign == 1)
			return (-1);
		if (nbr > 2147483648 && sign == -1)
			return (0);
		idx++;
	}
	return (sign * nbr);
}
