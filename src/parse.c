/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:21:40 by jimpark           #+#    #+#             */
/*   Updated: 2023/03/08 21:02:53 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	**tokenizing_cmds(char *cmd)
// {
// 	while (*cmd)
// }

void	make_nodes(char *line, int size, t_info *info)
{
	t_cmd	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		exit(1);
	if (info->head == NULL)
	{
		info->head = newnode;
		info->last = newnode;
	}
	else
	{
		info->last->next = newnode;
		info->last = newnode;
	}
	newnode->next = NULL;
	if (line[size] == '|')
	{
		newnode->is_pipe = 1;		// is_pipe 1을 파이프로
		line[size] = '\0';
	}
	else
		newnode->is_pipe = 0;		// is_pipe 0을 null로
	newnode->content = ft_strtrim(line, (char)32);
}

void	divide_cmd(char *line, t_info *info)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
		{
			make_nodes(ft_strdup(line), i, info);
			line = ft_substr(line, i + 1);
			i = -1;
		}
		i++;
	}
	make_nodes(line, i, info);
}

void	parse_cmds(char *line, t_info *info)
{
	check_syntax(line);				// 닫히지 않는 구문이 있는지 검사
	divide_cmd(line, &info);		// |, null 두 가지의 구분자를 기준으로 cmd를 나눔.
	while (info->head)
	{

	}
}
