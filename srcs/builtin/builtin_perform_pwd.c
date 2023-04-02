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
	char	*str;
	int		errno;

	str = getcwd(NULL, 0);
	if (str == NULL)
		exit (print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	ft_putstr_fd(str, fd[STD_OUT]);
	ft_putstr_fd("\n", fd[STD_OUT]);
	free(str);
	return (0);
}
