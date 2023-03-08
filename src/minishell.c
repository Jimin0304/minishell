/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:20:12 by jimpark           #+#    #+#             */
/*   Updated: 2023/03/08 20:22:17 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void set_input_mode(struct termios *term)
{
	tcgetattr(STDIN_FILENO, term); // STDIN으로부터 터미널 속성을 받아온다
	term->c_lflag &= ~(ECHOCTL);  // ICANON, ECHO 속성을 off
	tcsetattr(STDIN_FILENO, TCSANOW, term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
	}
	rl_replace_line("", 1);
	rl_redisplay();
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, sig_handler);
}

void	init_nodes(t_info *info)
{
	info->head = NULL;
	info->last = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_info			info;
	struct termios	term;

	if (argc != 1 || !**argv || !**envp)	//makefile 때문에 임시로 설정해둔 에러
		exit (1);
	set_input_mode(&term);
	set_signal();
	init_nodes(&info);
	while (1)
	{
		line = readline("minishell$ ");		// 기본함수 -> str를 출력하고 프롬프트를 열어서 표준입력으로 문자열을 입력받는다.
		if (!line)
		{
			printf("\033[1A"); // 커서를 위로 한 줄 올린다.
			printf("\033[10C"); // 커서를 10만큼 앞으로 전진시킨다.
			printf(" exit\n");
			break ;
		}
		check_syntax(line);
		add_history(line);					// 기본함수 -> 사용한 명령어를 history에 저장
		divide_cmd(line, &info);			// |, null 두 가지의 구분자를 기준으로 cmd를 나눔.
		free (line);
	}
	return (0);
}
