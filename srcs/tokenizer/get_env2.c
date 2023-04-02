/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:59:15 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 01:59:17 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	get_env_name_size(char *s)
{
	int		i;

	i = 0;
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
		return (i + 1);
	while (s[i] != '\0')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			break ;
		i++;
	}
	return (i);
}

char	*get_env_name(char *s)
{
	int		i;
	int		j;
	char	*name;

	j = 0;
	i = get_env_name_size(s);
	if (i == 0)
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (name == NULL)
		malloc_failed("get_env");
	while (i != 0)
	{
		name[j] = s[j];
		j++;
		i--;
	}
	name[j] = '\0';
	return (name);
}

char	*fix_dol(char *str)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != '\0')
		if (str[i] == -3)
			str[i] = '$';
	return (str);
}

void	check_next_dol(char *str, int i)
{
	if (str[i + 1] == '?')
		str[i] = -2;
	else if (!(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		str[i] = -3;
	else
		str[i] = -2;
}
