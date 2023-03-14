/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:41:27 by jimpark           #+#    #+#             */
/*   Updated: 2023/03/08 20:27:43 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		size;
	char	*dest;
	int		i;

	size = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (0);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	i;
	int	res;

	i = 0;
	res = ft_strlen(src);
	if (dstsize == 0)
		return (res);
	while ((src[i] != '\0') && (i < dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (res);
}

char	*ft_strtrim(char *s1, char set)
{
	int		start;
	int		end;
	char	*newstr;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while ((set == s1[start]) && (s1[start] != '\0'))
		++start;
	while ((set == s1[end]) && (start < end))
		--end;
	newstr = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!newstr)
		return (0);
	ft_strlcpy(newstr, &s1[start], end - start + 2);
	return (newstr);
}

char	*ft_substr(char *s, unsigned int start)
{
	char			*str;
	unsigned int	size;
	int				i;

	if (!s)
		return (0);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (size - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (s[start] != '\0')
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
