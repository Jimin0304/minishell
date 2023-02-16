/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:20:12 by jimpark           #+#    #+#             */
/*   Updated: 2023/02/16 23:48:16 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse_line(char *line) // 명령어(functions) 받아서 parsing 해야 됨
{
	// char	**result;
	// int		i;

	// i = 0;
	// while (line[i])
	// {
	// 	if (line[i] == 32 || (9 <= line[i] && line[i] <=13))
	// 		*result++ = ft_strdup(&line, i);
	// 	i++;
	// }
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**builtin_func;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		builtin_func = parse_line(line);
		free (line);
	}
	return (0);
}
