/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:59:37 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 11:29:05 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal2.h"
#include "minishell.h"
#include <signal.h>
#include <libft.h>

void	set_signal(void)
{
	set_terminal_print_off();
	signal(SIGINT, perform_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_origin(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, perform_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	perform_sigint_heredoc(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STD_ERROR);
	exit (1);
}
