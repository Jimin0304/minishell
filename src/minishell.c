/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:20:12 by jimpark           #+#    #+#             */
/*   Updated: 2023/03/01 23:22:45 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void set_input_mode(struct termios term)
{
	tcgetattr(STDIN_FILENO, &term); // STDIN으로부터 터미널 속성을 받아온다
	term.c_lflag &= ~(ECHOCTL);  // ICANON, ECHO 속성을 off
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("%s", "\n");
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

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_info			info;
	struct termios	term;

	if (argc != 1 || !**argv || !**envp)	//makefile 때문에 임시로 설정해둔 에러
		exit (1);
	set_input_mode(term);
	set_signal();
	while (1)
	{
		line = readline("minishell$ ");		// 기본함수 -> str를 출력하고 프롬프트를 열어서 표준입력으로 문자열을 입력받는다.
		if (!line)
			break ;
		add_history(line);					// 기본함수 -> 사용한 명령어를 history에 저장
		devide_cmd(line, &info);			// |, ;, null 세가지의 구분자를 기준으로 cmd를 나눔.
		free (line);
	}
	return (0);
}
