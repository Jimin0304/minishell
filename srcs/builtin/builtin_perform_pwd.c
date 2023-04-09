/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_perform_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:01:46 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:01:47 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "error.h"
#include "libft.h"

int	perform_pwd(int *fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (g_envp_list[i])
	{
		if (ft_strncmp("PWD=", g_envp_list[i], 4) == 0)
		{
			printf("%s\n", ft_substr2(g_envp_list[i], 4, \
				ft_strlen(g_envp_list[i]) - 4, "pwd"));
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
		exit (print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	return (0);
}
