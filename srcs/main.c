/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:10:44 by hwankim           #+#    #+#             */
/*   Updated: 2023/04/09 18:05:00 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "signal2.h"

#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*user_input;

	(void)argc;//사용되지 않는 변수들임 컴파일러의 경고를 피하기위해 작성
	(void)argv;//마찬가지
	g_envp_list = get_env(envp);
	while (1)
	{
		set_signal();
		user_input = readline("minishell $ ");
		if (user_input != NULL)
		{
			process_and_execution(user_input);//가공(토큰화,구문분석) + 실행 담당하는 함수
			free(user_input);
			continue ;
		}
		perform_sigterm();//쉘이 중단되거나 종료될 때 터미널의 시각적 측면을 처리
		break ;
	}
	set_terminal_print_on();
	exit(ft_atoi(g_envp_list[0]));
}

void	process_and_execution(char *user_input)
{
	t_tree	*tree;
	int		exit_flag;

	if (user_input[0] != '\0')//공백이 아닌 문자가 존재하면
	{
		add_history(user_input);
		tree = start_tokenize(user_input);//여기서 사용자 입력한 문자열은 공백 단위로 노드를 만들어서 연결리스트 생성 후 가장 오른쪽에 있는 노드에 대한 정보를 가진 트리를 반환
		if (tree == NULL)
			exit_flag = 0;
		else
		{
			exit_flag = parsing(&tree);//구문분석을 실시
			if (exit_flag == 0)
				exit_flag = execution(tree);//가공과정을 거친 입력값을 실행하는 과정
		}
		if (tree)
			tree_delete(tree);
		change_exit_flag(exit_flag);
	}
}
