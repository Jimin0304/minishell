/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:10:05 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 11:46:59 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "libft.h"
# include <sys/stat.h>
# include <errno.h>

int		print_errno(int fd, char *str1, char *str2, int rtn);
int		print_error(int fd, char *str1, char *str2, int rtn);

#endif
