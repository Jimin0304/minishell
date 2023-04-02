/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:02:00 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:02:01 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

#include <stdlib.h>

t_index	*make_idx(void)
{
	t_index	*new;

	new = malloc(sizeof(t_index));
	if (new == NULL)
		malloc_failed("make_idx");
	new->i = 0;
	new->j = 0;
	new->k = 0;
	return (new);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**malloc_env(int size)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * size);
	if (new == NULL)
		malloc_failed("malloc_env");
	while (i != size)
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}
