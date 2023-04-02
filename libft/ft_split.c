/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:16:54 by hwankim           #+#    #+#             */
/*   Updated: 2022/09/14 16:31:04 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words_size(char const *str, char c)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] != '\0' && str[i] != c)
			i++;
		cnt++;
	}
	return (cnt);
}

static char	*split_word(char const *str, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *) malloc(sizeof(char) * (len + 1));
	if (word == 0)
		return (0);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	free_words(char **words, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(words[i++]);
	free(words);
	return (0);
}

static int	split_word_list(char const *s, char c, char **words)
{
	int	start;
	int	i;
	int	word_n;

	i = 0;
	word_n = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		words[word_n] = split_word(s + start, i - start);
		if (words[word_n] == 0)
		{
			free_words(words, word_n);
			return (0);
		}
		word_n++;
	}
	words[word_n] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	if (s == NULL)
		return (NULL);
	words = (char **) malloc(sizeof(char *) * (count_words_size(s, c) + 1));
	if (words == 0)
		return (0);
	if (split_word_list(s, c, words) == 1)
		return (words);
	return (0);
}
