/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:58:54 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/05 17:03:46 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	skip_dquot(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\"')
	{
		i++;
		if (s[i] == '\0')
			return (0);
		while (s[i] != '\"' && s[i] != '\0')
				i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		if (s[i] == '\0')
			return (0);
		while (s[i] != '\'' && s[i] != '\0')
				i++;
	}
	if (s[i] == '\0')
		return (0);
	return (i);
}

int	check_dquot_error(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\"')
	{
		i++;
		while (s[i] != '\"' && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			return (-1);
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'' && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			return (-2);
	}
	return (i);
}

int	count_new_space(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count += 2;
		i++;
	}
	return (i + count);
}

int	check_input_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_whitespace(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
