#include "minishell.h"
#include "_tree.h"
#include "tokenizer.h"
#include "execution.h"
#include "mini_signal.h"
#include "_parser.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;

	(void)argc;
	(void)argv;
	g_envp_list = get_env(envp);//환경변수들을 복사해서 저장
	while (1)
	{
		set_signal();//시그널 처리
		str = readline("minishell $ ");//minishell $ 출력 및 표준입력 받아오기
		if (str != NULL)
		{
			run_minishell(str);//미니쉘 실행
			free(str);
			continue ;
		}
		break ;
	}
	setting_terminal();//터미널 속성 변경
	exit(ft_atoi(g_envp_list[0]));//정상종료
}

void	run_minishell(char *str)//사용자입력으로 받은 문자열을 인자로 받음
{
	t_tree	*tree;
	int		exit_status;

	if (check_str_whitespace(str))//공백문자가 아닌 문자가 존재하면 0,전부 다 공백이면 1
		;
	else if (str[0] != '\0')//공백문자가 아닌 문자가 존재시 만족
	{
		add_history(str);//히스토리에 사용자로부터 입력받은 문자열 저장
		tree = start_tokenize(str);//사용자로부터 입력받은 문자열을 공백을 단위로 정의한 기준에 따라 분류해서 연결리스트에 담은 뒤  top 노드를 가르키는 트리를 반환  
		if (tree == NULL)
			exit_status = 0;
		else
		{//?
			exit_status = parser(&tree);//위에서 분류된 노드를 트리구조로 재구조화
			if (exit_status == 0)
				exit_status = execution(tree);//실행
		}
		if (tree)
			tree_delete(tree);
		change_exit_status(exit_status);
	}
}
