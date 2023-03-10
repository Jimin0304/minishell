/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:19:11 by jimpark           #+#    #+#             */
/*   Updated: 2023/03/08 19:13:20 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
	int				type;
}				t_list;

typedef struct	s_info
{
	struct s_list	*head;
	struct s_list	*last;
}				t_info;

char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
int		ft_strlcpy(char *dst, char *src, int dstsize);
char	*ft_strtrim(char *s1, char set);
char	*ft_substr(char *s, unsigned int start);
void	make_nodes(char *line, int size, t_info *info);
void	divide_cmd(char *line, t_info *info);
void	check_syntax(char *line);

#endif
