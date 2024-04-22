/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:41:46 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/22 21:31:38 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c_handler(int signum)
{
	// struct termios		term;

	g_signal = signum;
	// tcgetattr(STDIN_FILENO, &term);
	// term.c_lflag |= ECHOCTL;
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ctrl_bs_handler(int signum)
{
	g_signal = signum;
}

void	before_command(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_bs_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_initializer(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_c_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
