/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_perform_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:01:28 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:01:29 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"

int	perform_env(int *fd)
{
	int	i;

	i = 1;
	while (g_envp_list[i] != NULL)
	{
		if (find_equal(g_envp_list[i]))
		{
			ft_putstr_fd(g_envp_list[i], fd[STD_OUT]);
			ft_putstr_fd("\n", fd[STD_OUT]);
		}
		i++;
	}
	return (0);
}

int	find_equal(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
