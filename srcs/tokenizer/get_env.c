/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:59:24 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/09 18:05:00 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**get_env(char **envp)
{
	char	**list;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (envp[len])
		len++;
	list = malloc_env(len + 2);//먼가 문제가 생김
	len = 1;
	list[0] = ft_strdup2("0", "get_env");//변화 1
	if (ft_isdigit(envp[0][0]))
		j++;
	while (envp[j])
	{
		if (ft_strncmp("OLDPWD=", envp[j], 7) == 0)
			list[len] = ft_strdup2("OLDPWD", "get_env");
		else
			list[len] = ft_strdup2(envp[j], "get_env");
		len++;
		j++;
	}
	list[len] = NULL;
	return (list);
}

char	*get_env_to_str(char *env)
{
	t_index	i;

	i.i = -1;
	i.j = 0;
	if (env == NULL)
		return (NULL);
	if (env[0] == '?' && env[1] == '\0')
		return (free_ret(env, g_envp_list[0]));
	while (g_envp_list[++i.i] != NULL)
	{
		if (env[0] == g_envp_list[i.i][0])
		{
			while (env[i.j] != '\0' && g_envp_list[i.i][i.j] \
			!= '\0' && g_envp_list[i.i][i.j] != '=')
			{
				if (env[i.j] != g_envp_list[i.i][i.j])
					break ;
				i.j++;
			}
			if (env[i.j] == '\0' && g_envp_list[i.i][i.j] == '=')
				return (free_ret(env, &g_envp_list[i.i][++i.j]));
		}
		i.j = 0;
	}
	return (free_ret(env, NULL));
}

char	*get_env_tokenizer(char *s)
{
	t_index	*indexs;
	char	*str;

	indexs = make_idx();
	str = ft_strdup2(s, "get_env");
	while (str[indexs->i] != '\0')
	{
		if (str[indexs->i] == '"')//"만나면
			indexs->j = check_double_flag(&str[indexs->i], indexs->j);//j는 double_flag값을 반환받음
		if (str[indexs->i] == '\'' && indexs->j == 0)//이 조건은 ""안에 '있을떄는 만족하지 않음 그러나 ""밖에 존재한다면 실행
			indexs->i += skip_dquot(&str[indexs->i]);//작은따옴표 안에 있는 $ 문자 또는 이스케이프 시퀀스는 일반 텍스트로 처리되어야하기 때문에 ''안에 문자들은 그냥 스킵
		if (str[indexs->i] == '$')
		{
			check_next_dol(str, indexs->i);
			if (str[indexs->i] == -2)
				str = get_merged_str(str, indexs);
			if (str == NULL)
				break ;
		}
		else if (str[indexs->i] != '\0')
			indexs->i++;
	}
	free(indexs);
	return (fix_dol(str));
}

char	*get_merged_str(char *str, t_index *i)
{
	char	*env;
	char	*env_name;

	env_name = get_env_name(&str[i->i + 1]);
	env = get_env_to_str(env_name);
	if (env)
		i->i += ft_strlen(env);
	str = get_merged_env_str(str, env);
	return (str);
}

char	*get_merged_env_str(char *s, char *env)
{
	int		i;
	char	*front;
	char	*rear;
	char	*merge1;
	char	*merge2;

	i = 0;
	while (s[i] != -2)
		i++;
	if (i != 0)
		front = ft_substr2(s, 0, i, "get_env");
	else
		front = NULL;
	if (s[get_env_name_size(&s[i + 1]) + i + 1] != '\0')
		rear = ft_strdup2(&s[get_env_name_size(&s[i + 1]) \
		+ i + 1], "get_env");
	else
		rear = NULL;
	free(s);
	merge1 = ft_strjoin_check_null(front, env);
	merge2 = ft_strjoin_check_null(merge1, rear);
	return (merge2);
}
