/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:57:05 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/10 15:27:21 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

// write newline - make readline realize it needs to be on that new line,
// erase currently written text from buffer, force update readline
void	sigint_handler(int signum)
{
	signum++;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	toggle_intercept(int toggle)
{
	static void	(*prev_int)(int);
	static void	(*prev_quit)(int);
	static int	i = 0;

	if (i == 0)
	{
		i++;
		prev_int = signal(SIGINT, sigint_handler);
		prev_quit = signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, prev_int);
		signal(SIGQUIT, prev_quit);
	}
	if (toggle == OFF)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (toggle == ON)
	{
		signal(SIGINT, prev_int);
		signal(SIGQUIT, prev_quit);
	}
}
