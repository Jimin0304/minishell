/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:11:28 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 02:11:29 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "error.h"
#include "builtin.h"

int	check_exit_status(int statloc)
{
	if ((statloc & 255) == 0)//and연산을 통해 하위 8비트가 모두 0아면 자식이 정상적으로 종료되었음을 의미
		return ((statloc >> 8) & 255);//오른쪽으로 8비트만큼 이동시키서 종료상태를 나타내는 비트 값을 반환
	return ((statloc & 127) + 128);// 자식이 정상적으로 종료되지 않았음(신호나 오류로 인해), statloc의 하위 7비트에 128을 더하여 종료 상태를 계산
}

int	init_fd(int **fd)
{
	if (fd == NULL)
		return (-1);
	(*fd) = ft_calloc2(3, sizeof(int), "fail init fd");
	(*fd)[0] = STD_IN;
	(*fd)[1] = STD_OUT;
	(*fd)[2] = STD_ERROR;
	return (1);
}

void	close2(int fd)
{
	if (close(fd) == -1)
		print_errno(STD_ERROR, NULL, NULL, 1);
}
