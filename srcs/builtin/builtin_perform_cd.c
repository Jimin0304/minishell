/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_perform_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:01:16 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:01:18 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "error.h"

int	perform_cd_home(int *fd)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		exit (print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	if (chdir(getenv("HOME")) != 0)
		return (print_cd_error(ft_strdup(getenv("HOME")), old_pwd, fd));
	change_pwd(old_pwd, fd);
	return (0);
}

int	perform_cd(char **s, int *fd)
{
	char	*dir;
	char	*save_dir;
	char	*old_pwd;

	if (s[1] == NULL || s[1][0] == '\0')
		return (perform_cd_home(fd));
	dir = ft_strdup2(s[1], "cd");
	if (dir[0] == '~' && (dir[1] == '\0' || dir[1] == '/'))
	{
		save_dir = ft_strjoin2(getenv("HOME"), &dir[1], "cd");
		free(dir);
		dir = save_dir;
	}
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		exit (print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	if (chdir(dir) != 0)
		return (print_cd_error(dir, old_pwd, fd));
	else
		change_pwd(old_pwd, fd);
	free (dir);
	return (0);
}

void	change_pwd(char *old_pwd, int *fd)
{
	char	*pwd;
	char	*pwd2;

	pwd = ft_strjoin2("OLDPWD=", old_pwd, "cd");
	g_envp_list = change_env(pwd);
	free(old_pwd);
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		exit (print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	pwd2 = ft_strjoin2("PWD=", old_pwd, "cd");
	g_envp_list = change_env(pwd2);
	free(old_pwd);
}

int	print_cd_error(char *dir, char *old_pwd, int *fd)
{
	print_errno(fd[STD_ERROR], "cd", dir, 0);
	free(old_pwd);
	free(dir);
	return (1);
}
