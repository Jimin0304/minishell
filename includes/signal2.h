/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwankim <hwankim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:10:27 by hwankim           #+#    #+#             */
/*   Updated: 2023/03/31 11:29:05 by hwankim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL2_H
# define SIGNAL2_H


void	set_signal(void);
void	set_signal_fork(void);
void	set_signal_origin(void);
void	set_signal_heredoc(void);
void	perform_sigint(int signum);
void	perform_sigquit(int signum);
void	perform_sigterm(void);
void	perform_sigint_heredoc(int signum);
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);
void	perform_sigint_fork(int signum);
void	check_fork_signal(int statloc);

#endif
