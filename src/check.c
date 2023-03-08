/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:12:42 by jimpark           #+#    #+#             */
/*   Updated: 2023/03/08 20:18:59 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_syntax(char *line)
{
	int	flag;

	flag = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			flag++;
		line++;
	}
	if (flag % 2 != 0)
	{
		printf("Syntax error: Unclosed quotes\n");
		exit (1);		// 추후에 error 함수로 바꾸기
	}
}
