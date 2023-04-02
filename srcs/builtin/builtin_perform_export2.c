/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_perform_export2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:01:42 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:01:43 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"

int	check_dup(char *str, char *env)
{
	int	j;

	j = 0;
	if (str[j] == env[j])
	{
		while (str[j] != '=' && str[j] != '\0')
		{
			j++;
			if (str[j] != env[j])
				break ;
		}
		if (str[j] == '\0' && env[j] == '=')
			return (2);
		if ((str[j] == '=' && env[j] == '=') || \
		(str[j] == '\0' && env[j] == '\0') || (str[j] == '=' && env[j] == '\0'))
			return (1);
	}
	return (0);
}

int	error_print_export(char *str, char *word, int *fd)
{
	ft_putstr_fd("minishell: export: ", fd[STD_ERROR]);
	ft_putstr_fd("`", fd[STD_ERROR]);
	ft_putstr_fd(word, fd[STD_ERROR]);
	ft_putstr_fd("\'", fd[STD_ERROR]);
	ft_putstr_fd(str, fd[STD_ERROR]);
	ft_putstr_fd("\n", fd[STD_ERROR]);
	return (1);
}
