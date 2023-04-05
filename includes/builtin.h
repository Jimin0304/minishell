/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:09:58 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/05 17:09:34 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
}	t_index;

t_index	*make_idx(void);

int		perform_export(char **word, int *fd);
char	**change_env_at_export(char *str, char **new_list, int i);
char	**change_env(char *str);
int		check_export_word(char *word, int *fd);
int		check_dup(char *str, char *env_list);
int		error_print_export(char *str, char *word, int *fd);
void	change_pwd(char *old_pwd, int *fd);
void	free_env(char **env);
int		perform_pwd(int *fd);
int		check_word(char *word);
int		perform_echo(char **word, int *fd);
int		perform_env(int *fd);
int		perform_cd(char **s, int *fd);
int		print_cd_error(char *dir, char *old_pwd, int *fd);
int		check_opt(char **s);
int		check_dequot(char *s);
int		find_equal(char *word);
char	**malloc_env(int size);
void	print_env(int *fd);
void	print_env_print_part(char *str, int *fd);
char	**sort_env(void);
char	*ft_strjoin2(char *s1, char *s2, char *s3);
char	*ft_strdup2(char *s1, char *s2);
char	*ft_substr2(char *s1, int start, int size, char *s2);
void	*ft_calloc2(size_t count, size_t size, char *s);
int		perform_unset(char **word, int *fd);
void	unset_env(t_index *idx);
int		check_unset_dup(char *str, char *env);
int		perform_exit(char **word, int *fd);
void	print_errmsg_at_exit(int *fd, char *copy_str);
int		get_envp_size(void);
void	check_next_dol(char *str, int i);

#endif
