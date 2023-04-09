/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_perform_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:01:54 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:01:55 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"

int	perform_unset(char **word, int *fd)
{
	t_index	*idx;

	idx = make_idx();
	idx->k = 1;
	while (word[idx->k] != NULL)
	{
		check_export_word(word[idx->k], fd);
		while (g_envp_list[idx->i] != NULL)
		{
			if (idx->i != 0 && check_unset_dup(word[idx->k], \
			g_envp_list[idx->i]) && g_envp_list[idx->i][0] != '_')
				unset_env(idx);
			idx->i++;
		}
		idx->i = 0;
		idx->k++;
	}
	free(idx);
	return (0);
}

void	unset_env(t_index *idx)
{
	free(g_envp_list[idx->i]);
	while (g_envp_list[idx->i + 1] != NULL)
	{
		g_envp_list[idx->i] = g_envp_list[idx->i + 1];
		idx->i++;
	}
	g_envp_list[idx->i] = g_envp_list[idx->i + 1];
}

int	check_unset_dup(char *str, char *env)
{
	int	j;

	j = 0;
	if (str[j] == env[j])
	{
		while (str[j] != '\0')
		{
			j++;
			if (str[j] != env[j])
				break ;
		}
		if (str[j] == '\0' && (env[j] == '=' || env[j] == '\0'))
			return (1);
	}
	return (0);
}
